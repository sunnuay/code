DROP SCHEMA IF EXISTS example CASCADE;
CREATE SCHEMA example;

CREATE TABLE example.users (
  id UUID PRIMARY KEY DEFAULT uuidv7(),
  username TEXT NOT NULL UNIQUE,
  password TEXT NOT NULL,
  settings JSONB NOT NULL
);

INSERT INTO example.users (username, password, settings) VALUES
('alice', 'YWxpY2U=', '{}'),
('bob', 'Ym9i', '{"theme": "dark"}');

SELECT * FROM example.users;
