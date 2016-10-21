-- DBWScript v3.10
-- Database: C:\Users\colorfulfool\Projects\fair-trade\docs\extra-mile\database.mdb

CREATE TABLE [Lecturer] (
	[name] NVARCHAR(20),
	[id] SMALLINT NOT NULL,
	CONSTRAINT [Lecturer$id] PRIMARY KEY ([id])
);
GO

CREATE TABLE [Project] (
	[dueTo] DATETIME,
	[task] NVARCHAR(20),
	[subject] NVARCHAR(20),
	[completeness] SMALLINT,
	[id] SMALLINT NOT NULL,
	[lecturer_id] SMALLINT NOT NULL,
	[student_id] SMALLINT NOT NULL,
	CONSTRAINT [Project$id] PRIMARY KEY ([id])
);
GO

CREATE TABLE [Student] (
	[name] NVARCHAR(20),
	[group] NVARCHAR(20),
	[id] SMALLINT NOT NULL,
	CONSTRAINT [Student$id] PRIMARY KEY ([id])
);
GO

CREATE INDEX [Project$lecturer_id1]
	ON [Project] ([lecturer_id]);
GO

CREATE INDEX [Project$student_id1]
	ON [Project] ([student_id]);
GO

ALTER TABLE [Project]
	ADD CONSTRAINT [Project$lecturer_id]
	FOREIGN KEY ([lecturer_id]) REFERENCES
		[Lecturer] ([id]);
GO

ALTER TABLE [Project]
	ADD CONSTRAINT [Project$student_id]
	FOREIGN KEY ([student_id]) REFERENCES
		[Student] ([id]);
GO

