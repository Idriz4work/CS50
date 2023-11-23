UPDATE show SET title = "How I Met Your Mother" WHERE title LIKE "How i met your mother";

UPDATE Show SET title = "Brooklyn Nine-Nine" WHERE title LIKE "B99";
UPDATE Show SET title = "Brooklyn Nine-Nine" WHERE title LIKE "Brooklyn%";
UPDATE Show SET title = "Game of Thrones" WHERE title LIKE "GoT";

SELECT * FROM shows ORDER BY title;