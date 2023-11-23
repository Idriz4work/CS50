SELECT COUNT(rating) AS number_ratings
FROM ratings
JOIN movies ON ratings.movie_id = movies.id
WHERE ratings.rating = '10.00';

-- To quit use .quit in sqlite3
