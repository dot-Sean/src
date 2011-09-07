/* "host=localhost port=5434 user=postgres password=edb dbname=postgres " */

DROP TABLE salesinfo;
CREATE TABLE salesinfo(date DATE, sales INTEGER);

CREATE OR REPLACE FUNCTION salesinfo_insert_trigger() RETURNS TRIGGER AS
$$
  DECLARE
    part text;
  BEGIN
    part := 'salesinfo_' || to_char(new.date, 'YYYY') ||
     'Q' || to_char(to_integer(new.date, 'MM') / 4);
    EXECUTE 'INSERT INTO ' || part || ' VALUES(($1).*)' USING new;
    RETURN NULL;
  END;
$$
LANGUAGE plpgsql;

DROP TABLE salesinfo_2009Q4;
CREATE TABLE salesinfo_2009Q4 (
  LIKE salesinfo
    INCLUDING INDEXES
    INCLUDING DEFAULTS
    INCLUDING CONSTRAINTS,
  CHECK (DATE '2009-10-01' <= date and date < DATE '2010-01-01')
) INHERITS (salesinfo);

INSERT INTO salesinfo_2009Q4 VALUES (DATE '2009-12-04', 9800);

DROP TABLE salesinfo_2010Q1;
CREATE TABLE salesinfo_2010Q1 (
  LIKE salesinfo
    INCLUDING INDEXES
    INCLUDING DEFAULTS
    INCLUDING CONSTRAINTS,
  CHECK (DATE '2010-01-01' <= date and date < DATE '2010-04-01')
) INHERITS (salesinfo);

INSERT INTO salesinfo_2010Q1 VALUES (DATE '2010-02-04', 19800);
INSERT INTO salesinfo_2010Q1 VALUES (DATE '2010-03-31', 3200);
