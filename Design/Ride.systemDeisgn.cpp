// System Design LLD code for ride sharing system
// File name: Ride.systemDeisgn.cpp
// Author: Shreedhar Goyal

#include <string>
#include <algorithm>
#include <stdexcept>
#include <cctype>
using namespace std;

struct Location {
    int x;
    int y;

    bool operator==(const Location& other) const {
        return x == other.x && y == other.y;
    }
};

enum class Gender {
    MALE,
    FEMALE,
    OTHER
};

enum class VehicleType {
    BIKE,
    AUTO,
    SEDAN,
    SUV
};

enum class RideCycle {
    ONGOING,
    CANCELLED,
    COMPLETED,
    WAITING
};

class Vehicle {
private:
    string vehicleID;
    string numberPlate;
    string model; //`{Company}+{CarName}+{Model}`
    VehicleType type;

    void validatePlate(const string& plate){
        if(plate.empty())
            throw invalid_argument("Invalid plate number");
    }
public:
    Vehicle(const string& ID, const string& plate, const string& mod, VehicleType vt):
        vehicleID(ID), numberPlate(plate), model(mod), type(vt){
            validatePlate(plate);
        }
    
    string getVehicleID() const { return vehicleID; }
    string getNumberPlate() const { return numberPlate; }
    string getModel() const { return model; }
    VehicleType getType() const { return type; }
};

class User {
protected:
    string userID;
    string name;
    Gender gender;
    string mobileNumber;
    string aadharNumber;
    double rating;

    void validateNumber(const string& mobile){
        if(mobile.size() != 10 || !all_of(mobile.begin(), mobile.end(), ::isdigit))
            throw invalid_argument("Invalid mobile number");
    }

    void validateAadhar(const string& aadhar){
        if(aadhar.size() != 12 || !all_of(aadhar.begin(), aadhar.end(), ::isdigit))
            throw invalid_argument("Invalid Aadhar number");
    }

public:
    User(const string& id, const string& name, Gender gender, const string& mobile, const string& aadhar, double initialRating)
        : userID(id), name(name), gender(gender), rating(initialRating) {
        validateNumber(mobile);
        validateAadhar(aadhar);

        this->mobileNumber = mobile;
        this->aadharNumber = aadhar;
    }

    virtual ~User() = default;

    string getID() const { return userID; }
    string getName() const { return name; }
    string getMobileNumber() const { return mobileNumber; }
    double getRating() const { return rating; }
    
    virtual void updateRating(double newRating) = 0;
    virtual string getRole() const = 0;
};

class Rider : public User {
public:
    Rider(const string& id, const string& name, Gender gender, const string& mobile, const string& aadhar, double initialRating)
        : User(id, name, gender, mobile, aadhar, initialRating) {}

    void updateRating(double newRating) override {
        rating = rating*0.9 + newRating*0.1;

        if(rating > 5.0) rating = 5.0;
        if(rating < 1.0) rating = 1.0;
    }

    string getRole () const override {
        return "RIDER";
    }
};

class Driver : public User {
private:
    Vehicle* vehicle;
    bool availability;
public:
    Driver(const string& id, const string& name, Gender gender, const string& mobile, const string& aadhar, double initialRating):
        User(id, name, gender, mobile, aadhar, initialRating) , vehicle(nullptr), availability(true) {}

    bool getAvailability() const {  return availability; }
    Vehicle* getVehicle() const { return vehicle; }
    
    void updateRating(double newRating) override {
        if (newRating > rating) // good behaviour is rewarded quickly
            rating = rating*0.9 + newRating*0.2;
        else if ( newRating < rating) // bad reviews aren't penalise dratically
            rating = rating*0.9 + newRating*0.05;
        
        if(rating > 5.0) rating = 5.0;
        if(rating < 1.0) rating = 1.0;
    }

    void assignVehicle(Vehicle* v) {
        this->vehicle = v;
    }
    
    void updateAvailability ( bool newAvailability ) {
        availability = newAvailability;
    }

    string getRole() const override {
        return "DRIVER";
    }
};

class baseFareCalculator {
public:
    virtual ~baseFareCalculator() = default;
    virtual double calculate(double distance) const = 0;
};

class baseBike : public baseFareCalculator {
public:
    double calculate(double distance) const override {
        return 10 + distance*10;
    }
};

class baseAuto : public baseFareCalculator {
public:
    double calculate(double distance) const override {
        return 20 + distance*15;
    }
};

class baseSedan : public baseFareCalculator {
public:
    double calculate(double distance) const override {
        return 50 + distance*30;
    }
};

class baseSUV : public baseFareCalculator {
public:
    double calculate(double distance) const override {
        return 100 + distance*50;
    }
};

baseFareCalculator* getBaseFare(VehicleType type){
    static baseBike bike;
    static baseAuto autoCalc;
    static baseSedan sedan;
    static baseSUV suv;

    switch(type){
        case VehicleType::BIKE : return &bike;
        case VehicleType::AUTO : return &autoCalc;
        case VehicleType::SEDAN : return &sedan;
        case VehicleType::SUV : return &suv;
        default : throw invalid_argument("No matching vehicle type");
    }
}

class Ride {
private:
    string rideID;
    Driver* driver;
    Rider* rider;
    RideCycle status;

    double payment;
    double rideDistance;

    Location startLoc;
    Location endLoc;

    void calculateFare(){
        if(status != RideCycle::COMPLETED)
            throw logic_error("Ride must first be completed");
        
        if(!driver || !driver->getVehicle())
            throw logic_error("Driver information insufficiet");
        
        baseFareCalculator* calculator = getBaseFare(driver->getVehicle()->getType());
        payment = calculator->calculate(rideDistance);
    }

public:
    Ride(const string& id,Rider* r, const Location& startingLocation, const Location& endingLocation) :
        rideID(id), rider(r), driver(nullptr), status( RideCycle::WAITING ), payment(0.0), rideDistance(0.0), 
        startLoc(startingLocation), endLoc(endingLocation) {
            if(!rider)
                throw invalid_argument("Ride must have a rider!");
            if(startingLocation == endingLocation)
                throw invalid_argument("Ride must have different start and end locations");
        }
    
    string getRideID() const { return rideID; }
    RideCycle getStatus() const { return status; }

    void assignDriver(Driver* d){
        if(status != RideCycle::WAITING)
            throw logic_error("Driver can be assigned only to waiting riders");
        
        if(!d || !d->getAvailability())
            throw logic_error("No driver available");
        
        driver = d;
        driver->updateAvailability(false);
    }

    void startRide(){
        if(status != RideCycle::WAITING)
            throw logic_error("Ride can only be started after WAITING");
        if(!driver)
            throw logic_error("Cannot start without driver");

        status = RideCycle::ONGOING;
    }

    void cancelRide(){
        if(status != RideCycle::WAITING)
            throw logic_error("Only waiting rides can be cancelled");
        
        status = RideCycle::CANCELLED;

        if(driver){
            driver->updateAvailability(true);
        }
    }
    
    void completeRide(){
        if(status != RideCycle::ONGOING)
            throw logic_error("Only ONGOING rides can be completed");
        
        status = RideCycle::COMPLETED;
        driver->updateAvailability(true);
        
        calculateFare();
    }
};
