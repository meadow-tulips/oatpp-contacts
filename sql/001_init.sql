
CREATE TABLE IF NOT EXISTS Contacts (
    name                    varchar (256) PRIMARY KEY,
    email                   varchar (256),
    "phoneNumbers"          varchar (15)[]
);

INSERT INTO Contacts
(name, email, "phoneNumbers") VALUES ('Avan Sharma', 'admin@domain.com', Array['83299293']);
