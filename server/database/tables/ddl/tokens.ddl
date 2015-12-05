CREATE TABLE tokens (
	id INTEGER PRIMARY KEY,
    access_token TEXT not null,
    token_type TEXT not null,
    creation_date VARCHAR(30) not null,
    expires_in INTEGER
)