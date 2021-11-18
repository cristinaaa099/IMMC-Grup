# IMMC-Grup
Proiect POO

## Objective
Developing a web application which allows student projects to be graded by anonymous juries of coleagues.

## Description
The application allows students projects to be graded by anonymous juries of peers. The application is built on a Single Page Application architecture and is accessible from the browser on the desktop, mobile devices or tablets (depending on user preference).

## Functionalities
### Students

+ In case you are a student member in a project team (PM) you can add a project and define a series of partial project deliverables. By registering you automatically become eligible as an evaluator.

+ As a PM you can add a demonstrative video or a link to a server hosting the deployed project for any partial deliverable.

+ When a partial deliverable is due, any student who is not a PM for a particular project can be randomly selected to be part of the project jury. A student which is a member of said jury can grade the project.

+ The grade for the project is anonymous and the total grade is calculated by omitting the lowest and highest grades and then averaging the remaining ones. The grades are 1-10 with at most 2 fractional digits.

### Professor

+ In case you are a professor you can see the results of the evaluation for each project, without being able to see the identity of the jury members.

!!!The application has a sistem of permissions. Only a member of the jury can add/modify grades and they can only modify their own grades. Grades can only be modified for a limited period of time.

