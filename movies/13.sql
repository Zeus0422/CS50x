SELECT DISTINCT p.name
FROM people p
JOIN stars s ON p.id = s.person_id
JOIN movies m ON s.movie_id = m.id
JOIN stars kevin_stars ON m.id = kevin_stars.movie_id
JOIN people kevin ON kevin_stars.person_id = kevin.id AND kevin.name = 'Kevin Bacon'
WHERE p.id <> kevin.id;
