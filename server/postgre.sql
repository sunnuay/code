DROP SCHEMA IF EXISTS public CASCADE;
CREATE SCHEMA public;

CREATE TABLE users (
  id INT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
  username TEXT NOT NULL UNIQUE,
  settings JSONB NOT NULL
);

INSERT INTO users (username, settings) VALUES
('alice', '{}'),
('bob', '{"theme": "dark"}');

SELECT * FROM users;
