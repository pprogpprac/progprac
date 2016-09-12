/* |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
**********************************************************************************
COP5725 - Database Management Systems - Homework1 - Naveen R. Iyer (niyer@ufl.edu)
**********************************************************************************
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/*==============================================================================*/

/*
MovieID Name                                 Rated  Category   ReleaseDate Length
1001    Lone Survivor                        R      Action     01/10/14    121
1002    Frozen                               PG     Animation  11/27/13    108
1003    Paranormal Activity:The Marked Ones  R      Horror     01/03/14    84
1004    American Hustle                      R      Drama      12/20/14    129
1005    Saving Mr. Banks                     PG-13  Drama      12/13/13    120
1006    Her                                  R      Romance    01/10/14    120
1007    The Hobbit 2                         PG-13  Action     12/13/13    161
1008    The Hunger Games 2                   PG-13  Action     11/22/13    146
*/

/* >>>>> (1) Create the MOVIE table.<<<<< START */
create table "MOVIE"
(
    "MovieID" integer,
    "Name" varchar(100) not null,
    "Rated" varchar(5),
    "Category" varchar(20),
    "ReleaseDate" date,
    "Length" number(3),
    primary key ("MovieID")
);
/* >>>>> (1) Create the MOVIE table.<<<<< END */
/*==============================================================================*/ 
 
/*==============================================================================*/
/* >>>>> (2) Insert the all the records into the table.<<<<< START */
insert into "MOVIE" values (1001, 'Lone Survivor', 'R', 'Action', TO_DATE('01-10-2014','MM-DD-YYYY'), 121);
insert into "MOVIE" values (1002, 'Frozen', 'PG', 'Animation', '27-NOV-2013', 108);
insert into "MOVIE" values (1003, 'Paranormal Activity: The Marked Ones', 'R', 'Horror', TO_DATE('01-03-2014', 'MM-DD-YYYY'), 84);
insert into "MOVIE" values (1004, 'American Hustle', 'R', 'Drama', TO_DATE('12-20-2014', 'MM-DD-YYYY'), 129);
insert into "MOVIE" values (1005, 'Saving Mr. Banks', 'PG-13', 'Drama', TO_DATE('12-13-2013', 'MM-DD-YYYY'), 120);
insert into "MOVIE" values (1006, 'Her', 'R', 'Romance', TO_DATE('01-10-2014', 'MM-DD-YYYY'), 120);
insert into "MOVIE" values (1007, 'The Hobbit 2', 'PG-13', 'Action', TO_DATE('12-13-2013', 'MM-DD-YYYY'), 161);
insert into "MOVIE" values (1008, 'The Hunger Games 2', 'PG-13', 'Action', TO_DATE('11-22-2013', 'MM-DD-YYYY'), 146);
/* >>>>> (2) Insert the all the records into the table.<<<<< END */
/*==============================================================================*/


/*==============================================================================*/
/* >>>>> (3) Find the list of movies that are released in 2014. <<<<< START */
select "Name" from "MOVIE" where extract(year from "ReleaseDate") = 2014;
/* Explanation: Extract the names ("Name") of movies released in the year 2014.
/* >>>>> (3) Find the list of movies that are released in 2014. <<<<< END */
/*==============================================================================*/

/*==============================================================================*/
/* >>>>> (4) Find the list of movies that is rated PG or PG-13, while it's not animation. <<<<< START */
select "Name" from "MOVIE" where (("Rated" like 'PG' or "Rated" like 'PG-13') and ("Category" not like 'Animation'));
/* >>>>> (4) Find the list of movies that is rated PG or PG-13, while it's not animation. <<<<< END */
/*==============================================================================*/

/*==============================================================================*/
/* >>>>> (5) Find the list of movies that is shorter than 2 hours and has 'the' in its name (case insensitive). <<<<< START */
select "Name" from "MOVIE" where (("Length" < 120) and regexp_like("Name", 'the', 'i'));
/* >>>>> (5) Find the list of movies that is shorter than 2 hours and has 'the' in its name (case insensitive). <<<<< END */
/*==============================================================================*/

/*==============================================================================*/
/* >>>>> (6) How many movies are in the ‘MOVIE’ table. <<<<< START */
select count(*) from "MOVIE";
/* >>>>> (6) How many movies are in the ‘MOVIE’ table. <<<<< END */
/*==============================================================================*/

/* NRI additional question: Find movies beginning with 'S' and ending with 's' */
select "Name" from "MOVIE" where (regexp_like("Name", '^S') and regexp_like("Name", 's$'));

/* Insert a new movie 'The Redemption' with any data,
then count the number of movies in the table,
then update its ReleaseDate,
then update its Rated,
then update its Name with 'Shawshank'
and then finally delete it */
insert into "MOVIE" values (1009, 'The Redemption', 'PG-13', 'Action', TO_DATE('18-1-2016', 'DD-MM-YYYY'), 380);

select count(*) from "MOVIE";

update "MOVIE" set "ReleaseDate" = TO_DATE('31-01-1947', 'DD-MM-YYYY') where "MovieID" = 1009;

update "MOVIE" set "Rated" = 'NRI' where "MovieID" = 1009;

update "MOVIE" set "Name" = 'The Shawshank Redemption' where "MovieID" = 1009;

delete from "MOVIE" where "MovieID" = 1009;

select "MovieID", "Name", "Category" from "MOVIE" where "Length" > 120;