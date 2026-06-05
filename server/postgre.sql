-- pg_ctl -D ~/.pgdata init
-- pg_ctl -D ~/.pgdata start -o "-k /tmp"
-- psql -h /tmp -d postgres -f server/postgre.sql

DROP TABLE IF EXISTS users;

CREATE TABLE users (
  id INT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
  username TEXT NOT NULL UNIQUE,
  settings JSONB NOT NULL
);

INSERT INTO users (username, settings) VALUES
('alice', '{}'),
('bob', '{"theme": "dark"}');

SELECT * FROM users;
