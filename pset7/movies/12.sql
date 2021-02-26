SELECT title

FROM movies JOIN stars sa ON (movies.id = sa.movie_id)
            JOIN people pa ON (sa.person_id = pa.id)
            JOIN stars sb ON (movies.id = sb.movie_id)
            JOIN people pb ON (sb.person_id = pb.id)
            
WHERE pa.name='Johnny Depp'
  AND pb.name='Helena Bonham Carter';