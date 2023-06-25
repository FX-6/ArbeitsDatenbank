-- Tabelle Admin anlegen

CREATE TABLE IF NOT EXISTS admins (
admin_id INTEGER,
email VARCHAR(255) NOT NULL UNIQUE,
passwort VARCHAR(255) NOT NULL,
PRIMARY KEY(admin_id)
);

-- Tabelle Admin befüllen

INSERT INTO
admins(admin_id, email, passwort)
VALUES
(1, 'peter@admin.de', '1234')


-- Tabelle Dozenten anlegen

CREATE TABLE IF NOT EXISTS dozenten (
dozent_id INTEGER,
vorname VARCHAR(255) NOT NULL,
nachname VARCHAR(255) NOT NULL,
email VARCHAR(255) NOT NULL UNIQUE,
passwort VARCHAR(255) NOT NULL,
login_versuche INT NOT NULL DEFAULT 0,
muss_passwort_andern INT CHECK(muss_passwort_andern IN (0, 1)) NOT
NULL DEFAULT 1,
PRIMARY KEY(dozent_id)
);

--Tabelle Dozenten befüllen

INSERT INTO
dozenten(dozent_id, vorname, nachname, email, passwort, login_versuche, muss_passwort_andern)
VALUES
(1, 'peter', 'maier', 'petermaier@test.de', '12345', 0, 0),
(2, 'hans', 'maier', 'hansmaier@test.de', '12345', 0, 0),
(3, 'max', 'mustermann', 'maxmustermann@test.de', '12345', 0, 0),
(4, 'martina', 'musterfrau', 'martinamusterfrau@test.de', '12345', 0, 0)


--Tabelle Arbeiten anlegen

CREATE TABLE IF NOT EXISTS arbeiten (
arbeit_id INTEGER,
typ INT CHECK(typ IN (0, 1, 2, 3)) NOT NULL,
betreuer INTEGER NOT NULL,
bearbeiter VARCHAR(255) NOT NULL,
bearbeitungsstatus INT CHECK(bearbeitungsstatus IN (0, 1)) NOT NULL,
studiengang VARCHAR(7) NOT NULL,
stichwortliste TEXT,
erlauterung TEXT,
von DATE,
bis DATE,
firma VARCHAR(255),
semester VARCHAR(6),
PRIMARY KEY(arbeit_id),
FOREIGN KEY(betreuer) REFERENCES dozenten(dozent_id)
);

--Tabelle Arbeiten befüllen

INSERT INTO
arbeiten(arbeit_id, typ, betreuer, bearbeiter, bearbeitungsstatus, studiengang, 
stichwortliste, erlauterung, von, bis, firma, semester)
VALUES
(1, 0, 1, 'Student01', 0, 'in', 'leer', 'leer', 01.01.2023, 01.06.2023, 'keine', '7')
(2, 1, 2, 'Student02', 0, 'in', 'leer', 'leer', 01.06.2023, 01.12.2023, 'keine', '3')
(3, 2, 3, 'Student03', 1, 'bwl', 'leer', 'leer', 01.01.2023, 01.06.2023, 'keine', '5')
