--
-- Installskydb.sql
--
-- Copyright Christophe Gros 2017
-- 
-- The present script is released under the General Public Licence
--

CREATE OR REPLACE LANGUAGE plpgsql;

SET client_min_messages=notice;

--
-- IsTable(tname)
-- Returns TRUE if table tname exists
--
CREATE OR REPLACE FUNCTION IsTable(VARCHAR) RETURNS Boolean AS $$
DECLARE
	Nb INTEGER;
	Na NAME;
BEGIN
	Na := CAST(Lower($1) as NAME);
	SELECT INTO Nb COUNT(relname) FROM pg_class WHERE pg_table_is_visible(oid) AND relname = Na;
	IF Nb = 1 THEN
		RETURN TRUE;
	ELSE
		RETURN FALSE;
	END IF;
END;
$$ LANGUAGE 'plpgsql';

--
-- IsFunction(fname)
-- Returns TRUE if function fname exists
--

CREATE OR REPLACE FUNCTION IsFunction(VARCHAR) RETURNS Boolean AS $$
DECLARE
	Nb INTEGER;
	Na NAME;
BEGIN
	Na := CAST(Lower($1) as NAME);
	SELECT INTO Nb COUNT(proname) FROM pg_catalog.pg_proc WHERE proname = Na;
	IF Nb = 1 THEN
		RETURN TRUE;
	ELSE
		RETURN FALSE;
	END IF;
END;
$$ LANGUAGE 'plpgsql';

--
-- IsField(fieldname, tname)
-- Returns TRUE if table tname contains a field named fieldname
--

CREATE OR REPLACE FUNCTION IsField(VARCHAR, VARCHAR) RETURNS Boolean AS $$
DECLARE
	Fld Name;
	Tbl Name;
	Nb INTEGER;
BEGIN
	Tbl := CAST(Lower($2) AS Name);
	Fld := CAST(Lower($1) AS Name);

	SELECT INTO Nb COUNT(attname) FROM pg_catalog.pg_attribute, pg_catalog.pg_class WHERE pg_catalog.pg_attribute.attrelid = pg_catalog.pg_class.oid AND relname = Tbl AND attname = Fld;
	If Nb = 1 THEN
		RETURN TRUE;
	ELSE
		RETURN FALSE;
	END IF;	
END;
$$ LANGUAGE 'plpgsql';

--
-- IsConstraint(cname)
-- Returns TRUE if constraint cname exists
-- 

CREATE OR REPLACE FUNCTION IsConstraint(VARCHAR) RETURNS Boolean AS $$
DECLARE
	Nb INTEGER;
	Na NAME;
BEGIN
	Na := CAST(Lower($1) as NAME);
	SELECT INTO Nb COUNT(conname) FROM pg_constraint WHERE conname = Na;
	IF Nb > 0 THEN
		RETURN TRUE;
	ELSE
		RETURN FALSE;
	END IF;
END;
$$ LANGUAGE 'plpgsql';

--
-- NewIcon(name, file)
-- insert a new icon name and file if it doesn't exist yet
--

CREATE OR REPLACE FUNCTION NewIcon(VARCHAR, VARCHAR) RETURNS Void AS $$
DECLARE
	Na ALIAS FOR $1;
	Fi ALIAS FOR $2;
	r RECORD;
	
BEGIN
	SELECT INTO r File FROM TypeIcons WHERE File = Fi;
	IF NOT FOUND THEN
		INSERT INTO TypeIcons(Idx, Name, File) VALUES(NEXTVAL('TypeIcons_Idx_Seq'), Na, Fi);
	END IF;
	RETURN;
END;
$$ LANGUAGE 'plpgsql';

--
-- SkylDbInit()
-- The main function for db creation or update
--

CREATE OR REPLACE FUNCTION InitSkyDb() RETURNS Void AS $$
DECLARE
	r RECORD;
	n VARCHAR;
        I Integer;
BEGIN

--
--	Basic tuff for sk 1.2 and onwards
--
	RAISE NOTICE 'Initial Level (1.2)';
	IF NOT IsTable('Data') THEN
		CREATE TABLE Data -- The Data table
		(
			Idx Int4 PRIMARY KEY, -- Unique Index
			Name VARCHAR   NOT NULL,
			BirthDay DATE  NOT NULL,
			BirthTime TIME NOT NULL,
			Gender CHAR    NOT NULL, -- M = male, F = female, n = neutral
			ChartType Int2 DEFAULT 1, -- 0 = Beginning 1 = End, etc...
			Daylight BOOL  DEFAULT 'f', --  If daylight time saving
			TimeZone NUMERIC(5, 2) DEFAULT '0.0',
			Comment TEXT, -- Free text
			PlaceIdx Int4  NOT NULL -- Place row index
		);
	END IF;
	IF NOT IsTable('Data_Idx_Seq') THEN
		CREATE SEQUENCE Data_Idx_Seq;
	END IF;
	IF NOT IsTable('Data_Name') THEN
		CREATE INDEX Data_Name ON Data (Name) ;
	END IF;
	IF NOT IsTable('Place') THEN
		CREATE TABLE Place -- The places table
		(
			Idx Int4 PRIMARY KEY, -- Row index
			Name VARCHAR, -- Name of place
			Latitude NUMERIC(5, 2)  NOT NULL, -- Latitude in decimal
			Longitude NUMERIC(5, 2) NOT NULL, -- Longitude in decimal
			CountryIdx Int4 DEFAULT 1 -- Index of relevant country
		);
	END IF;
	IF NOT IsTable('Place_Idx_Seq') THEN
		CREATE SEQUENCE Place_Idx_Seq;
	END IF;
	IF NOT IsTable('Place_Name') THEN
		CREATE INDEX Place_Name ON Place (Name) ;
	END IF;
	IF NOT IsTable('Country') THEN
		CREATE TABLE Country -- The countries table
		(
			Idx Int4 PRIMARY KEY, -- Unique index
			Name VARCHAR   NOT NULL, -- Country name
			TZFile VARCHAR NOT NULL -- Zone info file name
		);
	END IF;
	IF NOT IsTable('Country_Idx_Seq') THEN
		CREATE SEQUENCE Country_Idx_Seq;
	END IF;
	IF NOT IsTable('Country_Name') THEN
		CREATE INDEX Country_Name ON Country (Name) ;
	END IF;
	IF NOT IsTable('ObjRest') THEN
		CREATE TABLE ObjRest -- Restrictions data for each object i.e. planet, star, etc...
(
	Index Int4            NOT NULL, -- Restrictions set index
	ObjIndex Int2         NOT NULL, -- Object index
	Rest Bool             NOT NULL, -- If not visible
	OrbAdd  NUMERIC(4, 2) NOT NULL, -- Orb addition
	Influence Int2        NOT NULL -- Power of object
);
	END IF;
	IF NOT IsTable('ObjRest_Index') THEN
		CREATE INDEX ObjRest_Index ON ObjRest (Index);
	END IF;
	IF NOT IsTable('AspRest') THEN
		CREATE TABLE AspRest -- Restrictions data for each aspect
		(
			Index Int4        NOT NULL, -- Restrictions index
			AspIndex Int2     NOT NULL, -- Aspect index
			Rest Bool         NOT NULL, -- If not visible
			Orb NUMERIC(5, 2) NOT NULL, -- Orb
			Color Int2        NOT NULL, -- Color 0..15
			Influence Int2    NOT NULL -- Power
		);
	END IF;
	IF NOT IsTable('AspRest_Index') THEN
		CREATE INDEX AspRest_Index ON AspRest (Index);
	END IF;
	IF NOT IsTable('Restrictions') THEN
		CREATE TABLE Restrictions -- The restrictions table
		(
			Idx Int4 PRIMARY KEY, -- Restrictions unique index
			Name VARCHAR   UNIQUE NOT NULL, -- Name
			Houses Bool    NOT NULL, -- If houses used
			Exotic Bool    NOT NULL, -- If Exotic object used e.g. Apollo, etc...
			Stars Bool     NOT NULL, -- If stars used
			Minor Bool     NOT NULL, -- If Minor aspects used .e.g. Sesquiquadrate
			HousesSys Int2 NOT NULL, -- If houses system code .e.g. Placidus, etc...
			TrueNode Bool  NOT NULL, -- If true lunar node
			Sidereal Int2  NOT NULL  -- If Tropical or sidereal zodiac, and which one.
		);
	END IF;
	IF NOT IsTable('Restrictions_Idx_Seq') THEN
		CREATE SEQUENCE Restrictions_Idx_Seq;
	END IF;
	IF NOT IsTable('Restrictions_Name') THEN
		CREATE INDEX Restrictions_Name ON Restrictions (Name);
	END IF;
	IF NOT IsTable('TypeIcons') THEN
		CREATE TABLE TypeIcons 
		(
			Idx Int4 PRIMARY KEY, -- Typeicon index
			Name VARCHAR NOT NULL, -- Name of icon
			File VARCHAR NOT NULL -- Icon file
		);
	END IF;
	IF NOT IsTable('TypeIcons_Idx_Seq') THEN
		CREATE SEQUENCE TypeIcons_Idx_Seq MINVALUE 0 START 0;
	END IF;
	PERFORM NewIcon('Now', 'now.png');
	PERFORM NewIcon('Birth/Beginning', 'beginning.png');
	PERFORM NewIcon('Death/End', 'end.png');
	IF NOT IsTable('VData') THEN
		CREATE TABLE VData( -- table containing additional refernce for values storing
			DataIdx Int4 NOT NULL, -- Data row index
			RefIdx  Int4 NOT NULL, -- Original data row index
			RestIdx Int4 NOT NULL, -- Restrictions set index
			Type CHAR NOT NULL -- 'S' = single 'T' = transit 'D' = directions 'P' = progressions 'A' = add angle 'M' = mul by angle
		);
	END IF;
	IF NOT IsTable('VData_Idx_Key') THEN
		CREATE INDEX VData_Idx_Key ON VData(DataIdx);
	END IF;
	IF NOT IsTable('VDV') THEN
		CREATE VIEW VDV AS SELECT * FROM Data, VData WHERE Data.Idx = VData.DataIdx; -- This view displays all the data with saved values
	END IF;
	IF NOT IsTable('Obj') THEN
		CREATE TABLE Obj -- Objects values
		(
			DataIdx Int4 NOT NULL, -- Data row index
			Id CHAR(7) NOT NULL, -- Obj id, e.g. 'Sat' for Saturn
			Lon NUMERIC(8, 3) NOT NULL, -- Longitude in decimal
			Lat NUMERIC(8, 3) NOT NULL, -- latitude in decimal
			Retro BOOL NOT NULL, -- If retro
			InHouse Int2 NOT NULL -- House number
		);
	END IF;
	IF NOT IsTable('Obj_DataIdx_Key') THEN
		CREATE INDEX Obj_DataIdx_Key ON Obj(DataIdx);
	END IF;
	IF NOT IsTable('Asp') THEN
		CREATE TABLE Asp -- Aspects values
		(
			DataIdx Int4 NOT NULL, -- Data row index
			Objs CHAR(15) NOT NULL, -- Objs in aspect .e.g. 'Mar-Ven' for Mars-Venus aspect  
			AspId CHAR(3) NOT NULL, -- Aspect id .e.g. 'Opp' for opposition
			Orb NUMERIC(5, 3) NOT NULL, -- Local orb
			Pos CHAR NOT NULL -- If exact 'E', applying 'A', or separating 'S', aspect
		);
	END IF;
	IF NOT IsTable('Asp_DataIdx_Key') THEN
		CREATE INDEX Asp_DataIdx_Key ON Asp(DataIdx);
	END IF;
--
--	For sk 1.3
--
	RAISE NOTICE 'Level 1.3';
	PERFORM NewIcon('Success', 'up.png');
	PERFORM NewIcon('Failure', 'down.png');
	PERFORM NewIcon('Accident', 'accident.png');
	PERFORM NewIcon('Divorce/Rupture', 'divorce.png');
	PERFORM NewIcon('Solar Revolution', 'solar_rev.png');
	PERFORM NewIcon('Lunar Revolution', 'lunar_rev.png');
	PERFORM NewIcon('Marriage/Association', 'marriage.png');
	PERFORM NewIcon('Ordeal', 'ordeal.png');
	PERFORM NewIcon('Country', 'country.png');
	PERFORM NewIcon('Idea/Intuition', 'idea.png');
	PERFORM NewIcon('Illness', 'illness.png');
	PERFORM Newicon('Publication', 'publication.png');
	PERFORM NewIcon('Journey', 'journey.png');
	IF NOT IsField('S1', 'Restrictions') THEN
		ALTER TABLE Restrictions ADD S1 Int2; -- Score for conj. to Asc/MC;
		ALTER TABLE Restrictions ADD S2 Int2; -- Score for conj. to Dsc/FC/Sun
		ALTER TABLE Restrictions ADD S3 Int2; -- Score for masters of Asc/MC
		ALTER TABLE Restrictions ADD S4 Int2; -- Score for planets in their own sign
		ALTER TABLE Restrictions ADD S5 Int2; -- Score for plan conj. to master of Asc/MC.
		ALTER TABLE Restrictions ADD S6 Int2; -- Score per mastery
		ALTER TABLE Restrictions ADD S7 Int2; -- Score per aspect
		ALTER TABLE Restrictions ADD S8 Int2; -- Score when exalted planet

	END IF;
--
--	For sk 1.4
--
	RAISE NOTICE 'Level 1.4';
	IF NOT IsField('Keywords', 'Data') THEN
		ALTER TABLE Data ADD Keywords VARCHAR;
		ALTER TABLE Data ADD Accuracy Int2;
	END IF;
	IF NOT IsField('Code', 'Country') THEN
		ALTER TABLE Country ADD Code CHAR(3);
	END IF;
	PERFORM NewIcon('Meeting/Appointment', 'meeting.png');
	PERFORM NewIcon('Company', 'company.png');
	PERFORM NewIcon('Fest', 'Fest.png');
	IF NOT IsField('Angle', 'VData') THEN
		ALTER TABLE VData ADD Angle NUMERIC(8, 3);
	END IF;
--
--	For sk 1.5
--
	RAISE NOTICE 'Level 1.5';
	IF NOT IsTable('PlanetsRank') THEN
		CREATE TABLE PlanetsRank -- Stores the planets rank for VData DataIdx
		(
  			DataIdx Int4 NOT NULL, -- VData Index
 			 Planets CHAR(3)[] NOT NULL, -- Planets Ids (0..9)
  			Scores Int2[] NOT NULL -- Scores for planets
		);
	END IF;
	PERFORM NewIcon('Exact Aspect', 'exasp.png');
	PERFORM NewIcon('Direction Change', 'dirch.png');
	PERFORM NewIcon('Sign Change', 'signch.png');

--
--	For sk 1.6
--
	RAISE NOTICE 'Level 1.6';
	IF NOT IsField('Dst', 'Data') THEN
		ALTER TABLE Data ADD Dst NUMERIC(3,2) DEFAULT 0.0;
--		ALTER TABLE Data ALTER Dst SET DEFAULT 0.0;
		UPDATE Data SET Dst = CASE WHEN Daylight='t' THEN 1.0 ELSE 0.0 END;
	END IF;
	PERFORM NewIcon('Planet Rising', 'rising.png');
	PERFORM NewIcon('Eclipse Time', 'eclipse.png');

--
--	For sk 1.7
--
	RAISE NOTICE 'Level 1.7';
	SELECT INTO n Name FROM Country WHERE Name = 'GMT';
	IF n IS NULL THEN
		INSERT INTO Country (Idx, Name, TzFile) VALUES (nextval('Country_Idx_Seq'), 'GMT', 'GMT');
	END IF;
	SELECT INTO n Name FROM Place WHERE Name = 'ZeroGMT';
	IF n IS NULL THEN
		INSERT INTO Place (Idx, Name, Latitude, Longitude, CountryIdx) VALUES (nextval('Place_Idx_Seq'), 'ZeroGMT', 0.0, 0.0, (SELECT Idx FROM Country Where Name = 'GMT'));
	END IF;
	SELECT INTO n Name FROM Data WHERE Name = 'ZeroGMT';
	IF n IS NULL THEN
		INSERT INTO Data (Idx, Name, BirthDay, BirthTime, Gender, PlaceIdx) VALUES (nextval('Data_Idx_Seq'), 'ZeroGMT', '2000-01-01', '00:00:00', 'n', (SELECT Idx FROM Place Where Name = 'ZeroGMT'));
	END IF;
--
--	For sk 1.8
--
	RAISE NOTICE 'Level 1.8';
	IF NOT IsTable('LatPlace') THEN
		CREATE INDEX LatPlace ON Place(Latitude);
	END IF;
	IF NOT IsTable('LonPlace') THEN
		CREATE INDEX LonPlace ON Place(Longitude);
	END IF;
--
-- For sk 1.9
--
	RAISE NOTICE 'Level 1.9';
	IF NOT IsField('MpOrbSub', 'Restrictions') THEN
		ALTER TABLE Restrictions ADD MPOrbSub NUMERIC(5,3) DEFAULT 0.0;
	END IF;
	IF NOT IsField('Heliocentric', 'Restrictions') THEN
		ALTER TABLE Restrictions ADD Heliocentric BOOLEAN DEFAULT 'f';
	END IF;
	IF NOT IsField('Equatorial', 'Restrictions') THEN
		ALTER TABLE Restrictions ADD Equatorial BOOLEAN DEFAULT 'f';
	END IF;
--
-- For sk 1.9.2
--
	RAISE NOTICE 'Level 1.9.2';
	IF NOT IsField('Preload', 'Data') THEN
		ALTER TABLE Data ADD Preload BOOLEAN;
		ALTER TABLE Data ALTER COLUMN Preload SET DEFAULT 'f';
	END IF;
	IF NOT IsField('Preload', 'Restrictions') THEN
		ALTER TABLE Restrictions ADD Preload BOOLEAN;
		ALTER TABLE Restrictions ALTER COLUMN Preload SET DEFAULT 'f';
	END IF;
--
-- For sk 2.0
--
	RAISE NOTICE 'Level 2.0';
	IF NOT IsField('Automatic', 'Data') THEN
		ALTER TABLE Data RENAME Daylight TO Automatic;
		UPDATE Data Set Automatic = 'f';
	END IF;
	UPDATE Data Set Automatic = 't' WHERE Name = 'ZeroGMT';
--
-- For sk 2.1
--
	RAISE NOTICE 'Level 2.1';
	IF NOT IsConstraint('data_charttype_fkey') THEN
	  ALTER TABLE Data ADD FOREIGN KEY (ChartType) REFERENCES TypeIcons ON DELETE SET DEFAULT;
	END IF;
	IF NOT IsConstraint('data_placeidx_fkey') THEN
	  ALTER TABLE Data ADD FOREIGN KEY (PlaceIdx) REFERENCES Place ON DELETE RESTRICT;
	END IF;
	IF NOT IsConstraint('place_countryidx_fkey') THEN
	  ALTER TABLE Place ADD FOREIGN KEY (CountryIdx) REFERENCES Country ON DELETE CASCADE;
	END IF;
	ALTER TABLE Data ALTER Accuracy SET DEFAULT 0;
  IF NOT IsTable('Degrees') THEN
		CREATE TABLE Degrees(Idx Integer, Sabian VARCHAR);
  END IF;
--
-- For sk 2.2
--
	RAISE NOTICE 'Level 2.2';
	IF NOT IsField('J2g', 'Country') THEN
		ALTER TABLE Country ADD J2g TimeStamp;
		ALTER TABLE Country ALTER COLUMN J2g SET DEFAULT '1582-10-4';
	END IF;
	IF NOT IsTable('D1901') THEN
		CREATE TABLE D1901(Idx INTEGER, Seconds INTEGER, Date DATE);
		CREATE INDEX D1901_Idx_Date ON D1901(Idx, Date);
	END IF;
--
-- For sk 2.3
--
	  RAISE NOTICE 'Level 2.3';
		IF NOT IsTable('ExtraObjs') THEN
			CREATE TABLE ExtraObjs -- Stores the planets rank for VData DataIdx
			(
  				Idx Int4 UNIQUE NOT NULL, -- VData Index
 			 		Name VARCHAR UNIQUE NOT NULL, -- Planets Ids (0..9)
  				SName CHAR(3) UNIQUE NOT NULL -- Scores for planets
			) WITH OIDS;
		END IF;
		IF IsField('Exotic', 'Restrictions') THEN
	  	 ALTER TABLE Restrictions RENAME Exotic TO Extra;
		END IF;
--
-- For sk 2.4
--
        RAISE NOTICE 'Level 2.4';
	IF NOT IsTable('AspTbl') THEN
		CREATE TABLE AspTbl
		(
			Idx Int4 NOT NULL,
			AspKind CHAR NOT NULL,
			Date TIMESTAMP NOT NULL, -- Exact date of the event
			A CHAR(3), -- Object A's short name
			B CHAR(3), -- Object B's short name
			C CHAR(3), -- Object C's short name, if mid-point (C is the second term of the mid-point, A is the first one and B the aspecting planet)
			Asp CHAR(3), -- Aspect's short name
			Apos Real, -- Auxiliary angle A
			Bpos Real, -- Auxiliary angle B
			Sgn CHAR(3) -- Sign's short name (for sign change)
		);
		CREATE INDEX AspTbl_Idx ON AspTbl(Idx, Date);
		CREATE SEQUENCE AspTbl_Idx_Seq;
	END IF;
	IF IsTable('PlanetsRank') THEN
	  DROP TABLE PlanetsRank;
		IF NOT IsTable('Ranks') THEN
	  	 CREATE TABLE Ranks
	  	 (
								DataIdx Integer NOT NULL,  -- Idx from the corresponding Data
	    					Rank NUMERIC(3) NOT NULL,  -- 1..10
	    					Planet CHAR(3) NOT NULL,   -- 'Sol', 'Mar', etc...
	    					Score NUMERIC(4) NOT NULL, -- The planet's score
	    					FOREIGN KEY (DataIdx) REFERENCES Data ON DELETE CASCADE
	  		);
	  		CREATE INDEX Ranks_DataIdx_Rank ON Ranks(DataIdx, Rank);
				END IF;
	END IF;
	IF NOT IsField('ToSecond', 'Data') THEN
	  ALTER TABLE Data ADD ToSecond Boolean DEFAULT FALSE;
--	  ALTER TABLE Data ALTER ToSecond SET DEFAULT FALSE;
	END IF;
-- From now on, angles are real instead of NUMERIC(5,2), so that it can store seconds.
	ALTER TABLE Place ALTER Latitude TYPE Real;
	ALTER TABLE Place ALTER Longitude TYPE Real;
	ALTER TABLE Obj ALTER Lon TYPE NUMERIC(8,4);
	ALTER TABLE Obj ALTER Lat TYPE NUMERIC(8,4);
	IF IsTable('VDV') THEN
	  DROP VIEW Vdv;
	  ALTER TABLE Data ALTER Timezone TYPE Real;
	  ALTER TABLE Vdata ALTER Angle TYPE NUMERIC(8,4);
	  CREATE VIEW VDV AS SELECT * FROM Data, VData WHERE Data.Idx = VData.DataIdx;
	END IF;
	IF NOT IsField('Way', 'Asp') THEN
	  ALTER TABLE Asp ADD Way CHAR;
	END IF;
--
-- For sk 2.5
--
        RAISE NOTICE 'Level 2.5';
	IF NOT IsTable('Charts') THEN
	  CREATE TABLE Charts
	  (
	    Idx Int4 PRIMARY KEY, -- Chart index
	    Name VARCHAR UNIQUE NOT NULL, -- Its name.
	    Type CHAR NOT NULL, -- 'W' for std wheel chart, 'L' for list chart, etc...
	    Flags Integer, -- flags from ChartParams
	    ExtraFlags Integer, -- extra flags for wheel charts, tarots spreads etc...
	    Date TimeStamp DEFAULT Current_Timestamp -- The creation date of the chart.
	  );
	  CREATE SEQUENCE Chart_Idx_Seq;
	END IF;
	IF NOT IsTable('Ring') THEN
	 CREATE TABLE Ring
	 (
	   ChartIdx Int4 REFERENCES Charts ON DELETE CASCADE,  -- The chart's index
	   RingNb CHAR NOT NULL, -- '1' for ring 1, etc...
	   Subtype CHAR NOT NULL, -- 'S' for single, 'T' for transiting, etc...
	   Hidden Bool DEFAULT FALSE, -- If hidden of not
	   Angle Real, -- angle value for add or mul angle
	   DataIdx Int4 REFERENCES Data, -- The corresponding Dataset Idx
	   RestrIdx Int4 REFERENCES Restrictions -- The corresponding Restrictions group Idx
	 );
	 CREATE INDEX Ring_Idx ON Ring (ChartIdx, RingNb);
	 END IF;
	IF NOT IsTable('Tarots') THEN
		CREATE TABLE Tarots
		(
			Idx Int4 PRIMARY KEY, -- index
			Type CHAR NOT NULL, -- 'M' for major, 'W' for swords, 'C' for coins, 'S' for sticks and 'U' for cups
			Number SmallInt NOT NULL, -- 1..15
			Filename VARCHAR NOT NULL -- image filename
		);
	END IF;
	IF NOT IsTable('Spreads') THEN
	  CREATE TABLE Spreads
	  (
	    ChartIdx Int4 REFERENCES Charts ON DELETE CASCADE, -- The chart's index
	    TarotIdx Int4 REFERENCES Tarots ON DELETE CASCADE, -- The tarots's index
	    Pos SmallInt NOT NULL, -- 1..12
	    Level CHAR NOT NULL, -- '1', '2', '3';
	    Inversed Boolean DEFAULT FALSE -- TRUE if upside down
	  );
	END IF;
--
-- For sk 2.5.1
--
        RAISE NOTICE 'Level 2.5.1';
				PERFORM NewIcon('Tarots Spread', 'major.png');
	
--
-- For sk 2.5.5
--
				RAISE NOTICE 'Level 2.5.5';		
       IF NOT IsField('TrueSolarTime', 'Data') THEN
          ALTER TABLE Data ADD TrueSolarTime Boolean DEFAULT TRUE;
       END IF;
--
-- For sk 2.5.6
--
				RAISE NOTICE 'Level 2.5.6';
       IF NOT isField('Comment', 'Country') THEN
          ALTER TABLE Country ADD Comment VARCHAR;
       END IF;

--
-- For sk 3.1
--
				RAISE NOTICE 'Level 3.1';
			 IF NOT isField('Altitude', 'Place') THEN
			 		ALTER TABLE Place ADD Altitude REAL DEFAULT 0.0;
			 END IF;
			 IF NOT IsTable('Parts') THEN
	  	 		CREATE TABLE Parts
	  	 		(
					   Name VARCHAR NOT NULL,
						 P1 CHAR(3),
						 P2 CHAR(3),
						 P3 CHAR(3),
						 Night Boolean
					);
				END IF;

--
-- For sk 3.3
--
				RAISE NOTICE 'Level 3.3';
				IF NOT isField('State', 'VData') THEN
					 ALTER TABLE VData ADD State CHAR NOT NULL DEFAULT 'x'; -- 'M' = master, 'S' = slave, 'A' = alternative master, 'a' = alternative slave, 'x' = unknown
				END IF;
				IF NOT isField('State', 'Ring') THEN
					 ALTER TABLE Ring ADD State CHAR NOT NULL DEFAULT 'x'; -- see above
				END IF;
				IF IsFunction('Del_VData') THEN
					 DROP TRIGGER Del_VData_Trigger ON VData;
					 DROP FUNCTION Del_VData();
				END IF;
				IF NOT IsConstraint('vdata_dataidx_fkey') THEN
					 ALTER TABLE VData ADD FOREIGN KEY (DataIdx) REFERENCES Data ON DELETE CASCADE;
				END IF;
				IF NOT IsConstraint('obj_dataidx_fkey') THEN
					 ALTER TABLE Obj   ADD FOREIGN KEY (DataIdx) REFERENCES Data ON DELETE CASCADE;
				END IF;
				IF NOT IsConstraint('asp_dataidx_fkey') THEN
					 ALTER TABLE Asp   ADD FOREIGN KEY (DataIdx) REFERENCES Data ON DELETE CASCADE;
				END IF;
				IF NOT IsConstraint('ranks_dataidx_fkey') THEN
					 ALTER TABLE Ranks ADD FOREIGN KEY (DataIdx) REFERENCES Data ON DELETE CASCADE;
				END IF;
				IF IsFunction('Del_Restrictions') THEN
					 DROP TRIGGER Del_Restrictions_Trigger ON Restrictions;
					 DROP FUNCTION Del_Restrictions();
				END IF;
				IF NOT IsConstraint('vdata_restidx_fkey') THEN
					 ALTER TABLE VData ADD FOREIGN KEY (RestIdx) REFERENCES Restrictions ON DELETE CASCADE;
				END IF;
				IF NOT IsConstraint('objrest_index_fkey') THEN
					 ALTER TABLE ObjRest ADD FOREIGN KEY (Index) REFERENCES Restrictions ON DELETE CASCADE;
				END IF;
				IF NOT IsConstraint('asprest_index_fkey') THEN
					 ALTER TABLE AspRest ADD FOREIGN KEY (Index) REFERENCES Restrictions ON DELETE CASCADE;
				END IF;

--
-- For sk 3.4
--
				RAISE NOTICE 'Level 3.4';
				IF NOT IsTable('Interpret') THEN
					 CREATE TABLE Interpret
					 (
								Code VARCHAR, Lang CHAR(2), Text VARCHAR
					 );
					 CREATE INDEX Interpret_code_lang ON Interpret (Code, Lang);
				END IF;
				IF NOT isField('Lang', 'Degrees') THEN
					 ALTER TABLE Degrees ADD Lang CHAR(2) NOT NULL DEFAULT 'en';
					 IF IsConstraint('degrees_pkey') THEN
					 		ALTER TABLE Degrees DROP CONSTRAINT degrees_pkey;
					 END IF;
					 CREATE INDEX Degrees_idx_lang ON Degrees (Idx, Lang);
				END IF;
				IF NOT isField('Idx', 'Parts') THEN
					ALTER TABLE Parts ADD Idx Int4 NOT NULL;
					TRUNCATE Parts;
					CREATE INDEX Parts_idx ON Parts (Idx);
				END IF;

--
-- For sk 3.5
--
				RAISE NOTICE 'Level 3.5';
				PERFORM NewIcon('Ephem Day', 'ephemeris.png');
				PERFORM NewIcon('Primary Direction', 'pdir.png');
				PERFORM NewIcon('Converse Direction', 'cpdir.png');

--
-- For sk 3.7
--
			RAISE NOTICE 'Level 3.7';	
			IF NOT isField('S9', 'Restrictions') THEN
					 ALTER TABLE Restrictions ADD S9 Int2;
			END IF;
---
--- For sk 3.8
---
			RAISE NOTICE 'Level 3.8';
			IF NOT IsField('Dnpf', 'Restrictions') THEN
			  ALTER TABLE Restrictions ADD Dnpf Boolean DEFAULT 'f';
			END IF;
			IF NOT IsField('Southern', 'Restrictions') THEN
			  ALTER TABLE Restrictions ADD Southern Boolean DEFAULT 'f';
			END IF;
			IF NOT IsField('ProgFact', 'Restrictions') THEN
			  ALTER TABLE Restrictions ADD ProgFact Float DEFAULT 365.2422;
			END IF;
			IF NOT IsField('Asteroid', 'ExtraObjs') THEN
			  ALTER TABLE ExtraObjs ADD Asteroid Boolean DEFAULT 'f';
			END IF;
			PERFORM NewIcon('Lunar Occultation', 'occult.png');
---
--- For Sk 3.8.2
---
			RAISE NOTICE 'Level 3.8.2';
			IF NOT IsTable('InterTarots') THEN
				 CREATE TABLE Intertarots( Idx Integer, Type CHAR(1), Number Smallint, Lang CHAR(2), Text VARCHAR);
				 CREATE INDEX It_TNL ON Intertarots(Type, Number, Lang);
			END IF;
			IF NOT IsConstraint('asptbl_master_fkey') THEN
				 ALTER TABLE AspTbl ADD Master Int REFERENCES Data(Idx) ON DELETE CASCADE;
			END IF;
			IF NOT IsConstraint('asptbl_slave_fkey') THEN
				 ALTER TABLE AspTbl ADD Slave Int REFERENCES Data(Idx) ON DELETE CASCADE;
			END IF;
---
--- For Sk 4.0
---
			RAISE NOTICE 'Level 4.0';
			IF NOT IsTable('ConsNames') THEN
				 CREATE TABLE ConsNames(Idx Int4 PRIMARY KEY, Abr CHAR(3), Name VARCHAR(15));
			END IF;
			IF NOT IsTable('Boundaries') THEN
				 CREATE TABLE Boundaries(Idx Int4, Ra REAL, Dec REAL);
			END IF;
---
--- For Sk 4.0.3
---
				RAISE NOTICE 'Level 4.0.3';
				IF NOT IsTable('Stars') THEN
					 CREATE TABLE Stars(Name VARCHAR(26), Lang CHAR(2) DEFAULT 'en', Ab VARCHAR(9), SName VARCHAR(3));
				END IF;
---
--- For Sk 4.1
---
				RAISE NOTICE 'Level 4.1';
				IF NOT isField('Threshold', 'Restrictions') THEN
					 ALTER TABLE Restrictions ADD Threshold Int2 DEFAULT 0;
				END IF;
        SELECT INTO I COUNT(*) FROM Interpret WHERE Code like 'ip%';
       	IF I = 0 THEN
    			 INSERT INTO Interpret VALUES ('ip0', 'en', 'The Sun is a star of warmth, life, and light. Therefore, he emphasizes courage, loyalty, nobleness and generosity, but also pride, irascibility, andself-centrdness.'),
					 ('ip1', 'en', 'The Moon is a star of fertility, femininity, imagination and memory.'),
					 ('ip2', 'en', 'Mercury symbolizes intellectual capacity, thought process, comprehension and learning abilities, and all intellectual activities in general. He is the planet of communication and exchanges.'),
					 ('ip3', 'en', 'Venus is associated with love, beauty, well-being and gentleness. She describes one''s romantic life, affections, leisure, and the way one behaves with one''s love partners.'),
					 ('ip4', 'en', 'Mars is a combative energy and describes how one commands and takes action. He symbolizes virility, action, violence, courage and boldness. He bestows dynamis and enterprising spirit, but he can also turn the chart''s owner into a despotic, irascible and primary person.'),
					 ('ip5', 'en', 'Jupiter symbolizes abundance, warmth, blossoming, good luck and self-confidence. He also describes the potential for good fortune and the way the individual expresses his enthusiasm, his benevolence, as well as the way he integrates into the mainstream.'),
					 ('ip6', 'en', 'Saturn is synonymous with restriction. He symbolizes time and its implacable principle. He is associated with toughness, austerity, discipline and limitation.'),
					 ('ip7', 'en', 'Uranus is a dynamic and brutal energy. He brings about sudden and unforeseeable changes, new situations, revolutions, and disruptions. He is upsetting by nature because he symbolizes eccentricity, marginality, inventiveness, independence and dementia. He is also curt and terse, and sometimes, intolerant.'),
					 ('ip8', 'en', 'Neptune represents all things unreal and incomprehensible, as well as imagination, inspiration, faith, religion and mysticism.'),
					 ('ip9', 'en', 'Pluto represents occultism and all hidden sciences, mystery, death, the hereafter, deep self-questionings, as well as power such as that of the atom.'),
					 ('ip16', 'en', 'Ceres is associated with the mythological goddess of grain and harvest. It symbolizes both physical constitution and fertility.'),
					 ('ip17', 'en', 'Pallas is also used in modern Astrology. It represents intelligence, abstraction abilities and synthesizing talent.'),
					 ('ip18', 'en', 'Juno is the asteroid associated with the capacity to adjust to the spouse, and it also deals with the defence of personal rights.'),
					 ('ip19', 'en', 'Vesta indicates the capacity to dedicate oneself to a cause and to bring a higher level of efficiency into it.'),
					 ('ip14', 'en', 'Chiron represents wisdom, patience, and the capacity to relieve other people''s sufferings. It is known as the "Great Healer" of the Zodiac.'),
					 ('ip10', 'en', 'The North Node symbolizes the place of growth towards which we must progress even though we are often "new" and inexperienced as we start our journey.'),
					 ('ip11', 'en', 'The South Node symbolizes our acquired experience, and indirectly, the place we must part from, in order to develop. indirectly, the place we must part from, in order to develop.'),
					 ('ip12', 'en', 'Lilith symbolizes the "debt", or the karmic consequences of our deeds.'),
					 ('ip22', 'en', 'The East Point is related to how one is seen by other people, and to how one expresses one''s personality.'),
					 ('ih0', 'en', 'The Self, demeanour, and vitality.'),
					 ('ih1', 'en', 'Money earned and material goods.'),
					 ('ih2', 'en', 'Immediate surroundings, siblings, short trips, and studies.'),
					 ('ih3', 'en', 'Family, home, origins, heredity, and the father.'),
					 ('ih4', 'en', 'Love matters, pleasure, leisure, children, and creations.'),
					 ('ih5', 'en', 'Everyday life, daily work and colleagues, lower-ranking co-workers, and health.'),
					 ('ih6', 'en', 'Unions, marriage, other people, associations, and contracts.'),
					 ('ih7', 'en', 'Passions and crises, transformations, death, financial investments, and sexuality.'),
					 ('ih8', 'en', 'Abstract and higher concepts, spirituality, and foreign matters.'),
					 ('ih9', 'en', 'Social success, professional destiny, and the mother.'),
					 ('ih10', 'en', 'Friends, collective projects, supports and protections in life.'),
					 ('ih11', 'en', 'Enemies, difficulties, solitude, hidden ordeals, and secrets.'),
					 ('is0', 'en', 'Aries is Active, Demanding, Determined, Effective, Ambitious. Very clever and resourceful when motivated.'),
					 ('is1', 'en', 'Taurus is characterized by Security, Subtle strength, Appreciation, Instruction, Patience.'),
					 ('is2', 'en', 'Gemini is characterized by Communication, Indecision, Inquisitive, Intelligent, Changeable.'),
					 ('is3', 'en', 'Cancer is characterized by Emotion, Diplomatic, Intensity, Impulsive, Selective.'),
					 ('is4', 'en', 'Leo is characterized by Ruling, Warmth, Generosity, Faithful, Initiative. Confdence and charisma.'),
					 ('is5', 'en', 'Virgo is Analyzing, Practical, Reflective, Observation, Thoughtful. Can be scrutinizing and critical.'),
					 ('is6', 'en', 'Libra is characterized by Balance, Justice, Truth, Beauty, Perfection.'),
					 ('is7', 'en', 'Scorpio is Transient, Self-Willed, Purposeful, Unyielding. Not easy to pin down or predict. Prone to jealousy and possessivness.'),
					 ('is8', 'en', 'Sagittarius is Philosophical, Motion, Experimentation, Optimism.'),
					 ('is9', 'en', 'Capricorn is characterized by Determination, Dominance, Perservering, Practical, Willful. Easily accepts obligation and responsibility.'),
					 ('is10', 'en', 'Aquarius is characterized by Knowledge, Humanitarianism, Serious, Insightful, Duplicitous. Original thinker.'),
					 ('is11', 'en', 'Pisces is characterized by Fluctuation, Depth, Imagination, Reactive, Indecisive. Deeply intuitive, often lives and thinks in a different world than others.');
					 END IF;

					 SELECT INTO I attlen FROM pg_catalog.pg_attribute, pg_catalog.pg_class WHERE pg_catalog.pg_attribute.attrelid = pg_catalog.pg_class.oid AND relname = 'charts' AND attname = 'flags';
					 IF i = 4 THEN
					 		ALTER TABLE Charts ADD _flags BigInt;
							UPDATE Charts SET _flags = flags;
							ALTER TABLE Charts DROP flags;
							ALTER TABLE Charts RENAME _flags TO flags;
					 END IF;
  		PERFORM IfGroup();
END;
$$ LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION Del_Data () RETURNS TRIGGER AS $$
    DECLARE
	r RECORD;
    BEGIN
	SELECT INTO r RefIdx FROM VDV WHERE RefIdx = OLD.Idx AND DataIdx <> RefIdx;
	IF FOUND THEN
		RAISE EXCEPTION 'Cannot delete this data set. It is referenced by other data sets'; 
		RETURN NULL;
	END IF;
	--RAISE NOTICE 'DELETE Data Idx = %', OLD.Idx;
	DELETE FROM VData WHERE DataIdx = OLD.Idx;
        RETURN OLD;
    END;
$$ LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION IfSign(Real, Integer) RETURNS Boolean AS $$
    DECLARE
	angle ALIAS FOR $1;
	sn ALIAS FOR $2;
	d INTEGER;
    BEGIN
	d := FLOOR(angle / 30.0) + 1;
	IF d = sn THEN
		RETURN TRUE;
	ELSE
		RETURN FALSE;
	END IF;
    END;
$$ LANGUAGE 'plpgsql' IMMUTABLE;

CREATE OR REPLACE FUNCTION TObj(Int4, VARCHAR, Integer) RETURNS Boolean AS $$
   DECLARE
	r RECORD;
	o ALIAS FOR $2; 
   BEGIN
	SELECT INTO r DataIdx, Lon FROM Obj WHERE DataIdx = $1 AND Id ~* o AND IfSign(Lon, $3);
	IF FOUND THEN
		RETURN TRUE;
	ELSE
		RETURN FALSE;
	END IF;
    END;
$$ LANGUAGE 'plpgsql' STABLE;
 
CREATE OR REPLACE FUNCTION IfAsp(VARCHAR, VARCHAR, VARCHAR) RETURNS Boolean AS $$
    DECLARE
	asp VARCHAR;
	a VARCHAR;
	b VARCHAR;
	per CONSTANT VARCHAR := '%';
	da CONSTANT VARCHAR := '-';
    BEGIN
	asp := rtrim($1, ' ');
	a := rtrim($2, ' ');
	b := rtrim($3, ' ');
	IF a = '' THEN
		IF asp LIKE per || b || per THEN
			RETURN TRUE;
		END IF;
	ELSIF b = '' THEN
		IF asp LIKE per || a || per  THEN
			RETURN TRUE;
		END IF;
	ELSIF asp LIKE (a || da || b) OR asp LIKE (b || da || a) THEN
			RETURN TRUE;
	END IF;
    	RETURN FALSE;
    END;
$$ LANGUAGE 'plpgsql' IMMUTABLE;

CREATE OR REPLACE FUNCTION TAsp(Int4, VARCHAR, VARCHAR, VARCHAR) RETURNS Boolean AS $$
   DECLARE
	r RECORD;
	ai ALIAS FOR $2;
	o1 ALIAS FOR $3;
	o2 ALIAS FOR $4; 
   BEGIN
	SELECT INTO r DataIdx, AspId, Objs FROM Asp WHERE DataIdx = $1 AND AspId ~* ai AND IfAsp(Objs, o1, o2);
	IF FOUND THEN
		RETURN TRUE;
	ELSE
		RETURN FALSE;
	END IF;
    END;
$$ LANGUAGE 'plpgsql' STABLE;

CREATE OR REPLACE FUNCTION TRetr(Int4, VARCHAR) RETURNS Boolean AS $$
   DECLARE
	ai ALIAS FOR $2;
	r RECORD;
   BEGIN
	SELECT INTO r Id, Retro FROM Obj WHERE DataIdx = $1 AND Id ~* ai;
	IF FOUND THEN 
		RETURN r.Retro;
	END IF;
	RETURN FALSE;
   END;
$$ LANGUAGE 'plpgsql' STABLE;

CREATE OR REPLACE FUNCTION THouse(Int4, VARCHAR, Integer) RETURNS Boolean AS $$
   DECLARE
	ai ALIAS FOR $2;
	r RECORD;
   BEGIN
	SELECT INTO r InHouse FROM Obj WHERE DataIdx = $1 AND Id ~* ai;
	IF FOUND THEN
		IF r.InHouse = $3 THEN
			RETURN TRUE;
		END IF;
	END IF;
	RETURN FALSE;
   END;
$$ LANGUAGE 'plpgsql' STABLE;

CREATE OR REPLACE FUNCTION IfGroup() RETURNS Void AS $$
  DECLARE
    r RECORD;
  BEGIN
    SELECT INTO r Rolname FROM Pg_Authid WHERE Rolname = 'skyusers';
    IF NOT FOUND THEN
      CREATE GROUP SkyUsers;
    END IF;
  END;
$$ LANGUAGE 'plpgsql';

SELECT InitSkyDb();

CREATE OR REPLACE FUNCTION InitTables() RETURNS Void AS $$
DECLARE
	Pa VARCHAR;
	I Integer;
	J Integer;
BEGIN

SELECT Path INTO Pa FROM Path;

SELECT INTO I COUNT(*) FROM Degrees;
IF I = 0 THEN
        RAISE NOTICE 'Initialize Degrees';
	EXECUTE 'COPY Degrees ( idx, lang, sabian ) FROM ''' || Pa || '/Degrees.txt'' DELIMITER AS ''|''';
END IF;

SELECT INTO I COUNT(*) FROM Country;
IF I <= 2 THEN
        RAISE NOTICE 'Truncate and initialize D1901, Place & Country';
        ALTER TABLE Data  DROP CONSTRAINT data_placeidx_fkey;
--	ALTER TABLE D1901 DROP CONSTRAINT corr1901_idx_fkey;
--	ALTER TABLE Place DROP CONSTRAINT place_countryidx_fkey1;
        TRUNCATE D1901, Place, Country;
	EXECUTE 'COPY Country FROM ''' || Pa || '/Country.txt'' DELIMITER AS ''|''';
	ALTER TABLE Place ADD FOREIGN KEY (CountryIdx) REFERENCES Country ON DELETE CASCADE;
	SELECT INTO J setval('country_idx_seq', max(Idx)) FROM Country;
	EXECUTE 'COPY Place (Idx, Name, Latitude, Longitude, CountryIdx) FROM ''' || Pa || '/Place.txt'' DELIMITER AS ''|''';	
	SELECT INTO J setval('place_idx_seq', max(Idx)) FROM Place;
	ALTER TABLE Data ADD FOREIGN KEY (PlaceIdx) REFERENCES Place ON DELETE RESTRICT;
	EXECUTE 'COPY D1901 FROM ''' || Pa || '/D1901.txt'' DELIMITER AS ''|''';
	ALTER TABLE D1901 ADD FOREIGN KEY (Idx) REFERENCES Country(Idx) ON DELETE CASCADE;	
END IF;

SELECT INTO I COUNT(*) FROM ExtraObjs;
IF I = 0 THEN
        RAISE NOTICE 'Initialize ExtraObjs';
	EXECUTE 'COPY ExtraObjs(Idx, Name, SName) FROM ''' || Pa || '/ExtraObjs.txt'' DELIMITER AS ''|''';
END IF;
SELECT INTO I COUNT(*) FROM Tarots;
IF I = 0 THEN
        RAISE NOTICE 'Initialize Tarots';
	EXECUTE 'COPY Tarots FROM ''' || Pa || '/Tarots.txt'' DELIMITER AS ''|''';
END IF;
SELECT INTO I COUNT(*) FROM Parts;
IF I = 0 THEN
        RAISE NOTICE 'Initialize Arabic Parts';
	EXECUTE 'COPY Parts(Idx, Name, P1, P2, P3, Night) FROM ''' || Pa || '/Parts.txt'' DELIMITER AS ''|''';
END IF;

SELECT INTO I COUNT(*) FROM Interpret;
IF I = 0 THEN
        RAISE NOTICE 'Initialize Interpretation';
	EXECUTE 'COPY Interpret FROM ''' || Pa || '/Interpret.txt'' DELIMITER AS ''|''';
END IF;

SELECT INTO I COUNT(*) FROM Intertarots;
IF I = 0 THEN
        RAISE NOTICE 'Initialize Interpretation Tarots';
	EXECUTE 'COPY Intertarots FROM ''' || Pa || '/Intertarots.txt'' DELIMITER AS ''|''';
	ALTER TABLE Intertarots ADD FOREIGN KEY (Idx) REFERENCES Tarots ON DELETE CASCADE;
END IF;
SELECT INTO I COUNT(*) FROM ConsNames;
IF I = 0 THEN
        RAISE NOTICE 'Initialize Names of constellations';
	EXECUTE 'COPY ConsNames FROM ''' || Pa || '/ConsNames.txt'' DELIMITER AS ''|''';
END IF;
SELECT INTO I COUNT(*) FROM Boundaries;
IF I = 0 THEN
        RAISE NOTICE 'Initialize Data for constellations';
	EXECUTE 'COPY Boundaries FROM ''' || Pa || '/Boundaries.txt'' DELIMITER AS ''|''';
	ALTER TABLE Boundaries ADD FOREIGN KEY (Idx) REFERENCES ConsNames ON DELETE CASCADE;
END IF;
SELECT INTO I COUNT(*) FROM Stars;
IF I = 0 THEN
	 RAISE NOTICE 'Initialize Stars';
	 EXECUTE 'COPY Stars FROM ''' || Pa || '/Stars.txt'' DELIMITER AS ''|''';
END IF;
END;
$$ LANGUAGE 'plpgsql';

SELECT InitTables();
DROP FUNCTION InitTables();
DROP VIEW Path;

CREATE OR REPLACE FUNCTION GetInter(c VARCHAR, l CHAR(2)) RETURNS VARCHAR AS $$
			 SELECT COALESCE((SELECT Text FROM Interpret WHERE Lang = l AND Code = c), (SELECT Text FROM Interpret WHERE Lang = 'en' AND Code = c));
$$ LANGUAGE SQL;

GRANT SELECT, INSERT, UPDATE, DELETE ON Data, Place,  Country, ObjRest, AspRest, Restrictions, VData, VDV, Obj, Asp, AspTbl, Ranks, Charts, Ring, Spreads TO GROUP SkyUsers;

GRANT SELECT, UPDATE, USAGE ON Data_Idx_Seq, Place_Idx_Seq, Country_Idx_Seq, Restrictions_Idx_Seq, AspTbl_Idx_Seq, Chart_Idx_Seq TO GROUP SkyUsers;

GRANT SELECT ON TypeIcons, TypeIcons_Idx_Seq, Degrees, ExtraObjs, D1901, Tarots, Parts, Interpret, Intertarots, ConsNames, Boundaries, Stars TO GROUP SkyUsers;

GRANT EXECUTE ON FUNCTION IfSign(Real, Integer), TObj(Int4, VARCHAR, Integer), IfAsp(VARCHAR, VARCHAR, VARCHAR), TAsp(Int4, VARCHAR, VARCHAR, VARCHAR), TRetr(Int4, VARCHAR), THouse(Int4, VARCHAR, Integer), GetInter(c VARCHAR, l CHAR(2)) TO GROUP SkyUsers;

CREATE TRIGGER Del_Data_Trigger BEFORE DELETE ON Data
	FOR EACH ROW EXECUTE PROCEDURE Del_Data();

DROP FUNCTION InitSkyDb();
DROP FUNCTION IsField(VARCHAR, VARCHAR);
DROP FUNCTION IsTable(VARCHAR);
DROP FUNCTION IsFunction(VARCHAR);
DROP FUNCTION IsConstraint(VARCHAR);

CREATE OR REPLACE VIEW Version AS SELECT 4.1 AS V;
GRANT SELECT ON Version TO GROUP SkyUsers;

ANALYZE;
