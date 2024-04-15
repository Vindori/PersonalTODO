CREATE TABLE AppUser
(
    id       INTEGER PRIMARY KEY,
    username VARCHAR UNIQUE,
    email    VARCHAR UNIQUE,
    password VARCHAR,
    role     VARCHAR
);

INSERT INTO AppUser
    (username, email, password, role)
VALUES ('admin', 'admin@domain.com', 'admin', 'ROLE_ADMIN');


CREATE TABLE Todo
(
    todo_id INTEGER PRIMARY KEY,
    title   VARCHAR,
    done    INTEGER
);