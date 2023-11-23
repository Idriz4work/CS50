-- Select distinct person_id from directors with a rating of 9.0
SELECT DISTINCT(directors.person_id)
FROM directors
JOIN ratings ON directors.movie_id = ratings.movie_id
WHERE ratings.rating = 9.0

UNION

-- Select distinct person.name from people who are directors
SELECT DISTINCT(people.name)
FROM people
JOIN directors ON people.id = directors.person_id;
