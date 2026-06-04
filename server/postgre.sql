-- pg_ctl -D ~/.pgdata init
-- pg_ctl -D ~/.pgdata start -o "-k /tmp"
-- psql -h /tmp -d postgres -f server/postgre.sql

CREATE TABLE IF NOT EXISTS users (
  id INT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
  username TEXT NOT NULL UNIQUE,
  settings JSONB NOT NULL
);

INSERT INTO users (username, settings) VALUES
('alice', '{}'),
('bob', '{"theme": "dark"}')
ON CONFLICT (username) DO NOTHING;

SELECT * FROM users;
