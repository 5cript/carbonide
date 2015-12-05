CREATE TABLE users (
	id INTEGER PRIMARY KEY,
	name VARCHAR(50) not null,
    token INTEGER,
    FOREIGN KEY (token) REFERENCES tokens(id)
)