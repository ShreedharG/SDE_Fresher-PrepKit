https://leetcode.com/studyplan/top-sql-50/
###### Find Customer Referee
```
SELECT name
FROM customer
where referee_id != 2 or referee_id is NULL;
```

###### Recyclable and Low Fat 
```
SELECT product_id
FROM products
WHERE low_fats = 'Y' AND recyclable = 'Y';
```

###### Big Countries
```
SELECT name, population, area
FROM world
WHERE area >= 3000000 or population >= 25000000;
```

###### Article Views
```
SELECT DISTINCT author_id AS id
FROM Views
WHERE author_id = viewer_id
ORDER BY author_id;
```

###### Invalid Tweets
```
SELECT tweet_id
FROM tweets
WHERE LENGTH(content) > 15
```

###### Product Sales
```
SELECT p.product_name, s.year, s.price
FROM Sales AS s
INNER JOIN Product AS p
ON s.product_id = p.product_id;
```

###### Replace Employee ID
```
SELECT unique_id, name FROM Employees
LEFT JOIN EmployeeUNI
ON Employees.id = EmployeeUNI.id;
```

###### Customer Analysis
```
SELECT customer_id, COUNT(*) AS count_no_trans FROM visits v
JOIN

(SELECT v.visit_id FROM Visits as v
LEFT JOIN Transactions as t
ON v.visit_id = t.visit_id
WHERE t.transaction_id IS NULL) no_trans
  
ON v.visit_id = no_trans.visit_id
GROUP BY customer_id;
```

###### Weather Rise
```
SELECT w1.id
FROM Weather as w1
JOIN Weather as w2
ON DATEDIFF(w1.recordDate, w2.recordDate) = 1
AND w1.temperature > w2.temperature;
```

###### Employee Bonus
```
SELECT e.name, b.bonus
FROM Employee as e
LEFT JOIN Bonus as b
ON e.empID = b.empID
WHERE b.bonus < 1000 OR b.bonus IS NULL;
```

###### Managers with 5 Reports
```
SELECT name FROM Employee as e
JOIN
  
(SELECT managerId FROM Employee
GROUP BY managerId
HAVING COUNT(*) >=5) m
  
ON e.id = m.managerId;
```

###### Students and Examinations
```
SELECT t.student_id,t.student_name,t.subject_name,COUNT(e.student_id) as attended_exams
FROM
    (SELECT student_id, student_name, subject_name
    FROM students
    CROSS JOIN subjects) AS t
LEFT JOIN Examinations AS e
ON
    t.student_id = e.student_id AND
    t.subject_name = e.subject_name

GROUP BY
    t.student_id,
    t.student_name,
    t.subject_name

ORDER BY
    t.student_id,
    t.subject_name;
```

###### Not Boring Movies
```
SELECT * FROM Cinema
WHERE id%2 = 1 AND description != "boring"
ORDER BY rating DESC;
```

###### Project Employees
```
SELECT p.project_id, ROUND(AVG(e.experience_years), 2) AS average_years
FROM Project AS p
LEFT JOIN Employee AS e
ON p.employee_id = e.employee_id
GROUP BY project_id;
```

###### Average Selling Price
```
SELECT 
	p.product_id, 
	ROUND(IFNULL(SUM(p.price*us.units)/SUM(us.units),0),2) AS average_price
FROM Prices AS p
LEFT JOIN UnitsSold AS us
ON
    p.product_id = us.product_id
    AND us.purchase_date BETWEEN p.start_date AND p.end_date
GROUP BY product_id;
```

###### Classes with at least 5 Students
```
SELECT class FROM Courses
GROUP BY class
HAVING COUNT(*)>=5;
```

###### Number of Unique Subjects Taught by Each Teacher
```
SELECT teacher_id, COUNT(DISTINCT subject_id) AS cnt
FROM Teacher
GROUP BY teacher_id;
```

###### Find Followers Count
```
SELECT user_id, COUNT(*) AS followers_count
FROM Followers
GROUP BY user_id
ORDER BY user_id;
```

###### Biggest Single Number
```
SELECT IFNULL(

(SELECT *
FROM MyNumbers
GROUP BY num
HAVING COUNT(*)=1
ORDER BY num DESC
LIMIT 1), null)

AS num;
```

###### Customers Who Bought All Products
```
SELECT customer_id
FROM Purchases
GROUP BY customer_id
HAVING COUNT(DISTINCT product_key) = (SELECT COUNT(*) FROM Product);
```

###### User Activity for Past 30 Days
```
SELECT activity_date as day, COUNT(DISTINCT user_id) as active_users
FROM Activity
WHERE DATEDIFF('2019-07-27', activity_date) BETWEEN 0 AND 29
GROUP BY activity_date;
```

###### Percentage of Users in Each Contest
```
SELECT 
	r.contest_id, 
	ROUND( (COUNT(*)/(SELECT COUNT(*) FROM Users))*100, 2) as percentage
FROM Register AS r
JOIN Users AS u
ON r.user_id = u.user_id
GROUP BY r.contest_id
ORDER BY 
	percentage DESC, 
	r.contest_id ASC;
```

###### Queries Quality and Percentage of Query
```
SELECT
    q.query_name,
    ROUND(AVG(q.rating/q.position),2) AS quality,
    ROUND(100*SUM(CASE WHEN q.rating < 3 THEN 1 ELSE 0 END)/COUNT(*),2) AS poor_query_percentage

FROM Queries AS q
GROUP BY q.query_name;
```

###### Number of Unique Subjects of Teachers
```
SELECT teacher_id, COUNT(DISTINCT subject_id) as cnt
FROM Teacher
GROUP BY teacher_id;
```

###### Monthly Transactions
```
SELECT
    DATE_FORMAT(trans_date, '%Y-%m') AS month, country,
    COUNT(*) AS trans_count,
    SUM(CASE WHEN state='approved' THEN 1 ELSE 0 END) AS approved_count,
    SUM(amount) AS trans_total_amount,
    SUM(CASE WHEN state='approved' THEN amount ELSE 0 END) AS approved_total_amount
FROM Transactions
GROUP BY month, country;
```


Return - [[SDE Prep Kit]]

