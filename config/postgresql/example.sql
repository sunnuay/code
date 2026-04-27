-- initdb -D ~/.pgdata
-- pg_ctl -D ~/.pgdata -o "-k /tmp" start
-- psql -h /tmp -d postgres -f config/postgresql/example.sql

DROP SCHEMA IF EXISTS example CASCADE;
CREATE SCHEMA example;

CREATE TABLE example.users (
  id UUID PRIMARY KEY DEFAULT uuidv7(),
  username TEXT NOT NULL UNIQUE,
  password TEXT NOT NULL,
  settings JSONB NOT NULL DEFAULT '{}'
);

INSERT INTO example.users (username, password) VALUES
('alice', 'aaaaa'),
('bob', 'bbbbb');

SELECT * FROM example.users;
