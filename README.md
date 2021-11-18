# IMMC-Grup
Proiect POO


# Continuous-Feedback-App

## Objective
Developing a web application which enables users to provide continous feedback to an activity


## Description
The application must enable users to provide continuous feedback to a course or tutorial.

The application is built on a Single Page Application architecture and is accessible from the browser on the desktop, mobile devices or tablets (depending on user preference).

## Functionalities: 
+ As a professor i can define an activity at a particular date, with a description  and a unique access code for the activity. The activity is accessible for a set period of time.

+ As a student, i can input a code to participate in a defined activity. The code can be used for the duration of the activity.

+ As a student who has accessed an activity I have access to an interface split into 4 rectagles each containing an emoticon (smiley face, frowny face, surprised face, confused face). At any time i can press an emoticon to react to the activity. As a student I can add an unlimited number of feedback instances.

+ As a professor I can see the continuous feedback stream, with each feedback instance associated to the time it was generated at. I can only see the feedback as anonymous. For myself the feedback is available both during and after the activity.


## Available endpoints so far
### Student router: /student-api
`/students : Handle get request => response: a json array with all the students`

`/students/add : Handle post requests to /students/add => add a student to the database`

`/students/add/:id : Handle delete request to /students/:id => delete a student by its id`

`/students/:sid/feedbacks : Handle get request to /students/:sid/feedbacks => response: a json array with all the feedback that a student has`

`/students/:sid/:aid/feedbacks: Handle get request to /students/:sid/:aid/feedbacks => response: a json array with all the feedback that a student has on a specific activity`
### Group router: /group-api
`/groups : Handle get request to /groups => response: a json array with all the groups`

`/groups/add : Handle post request to /groups/add => using a json body add a group to the db`

`/groups/:gid/students : Handle get request to /group-api/groups/:gid/students => response: a json array with all the students that that are in a specific group`

`/groups/:gid/student/add : Handle post request to /group-api/groups/:gid/student/add => create a student and bond it with a group (group identified by id)`
### Activity router: /activity-api
`/activities : Handle get request to /activities => response: a json array with all the activities from the database`

`/activities/add : Handle post request to /activities/add => add a new activity to the db`

`/activities/:aid : Handle put request to /activities/:aid => update an existing activity`

`/activity-api/:aid : // Handle get request to /activity-api/:aid => get activity by id`

`/activities/:aid/update-count-emoji1 : Handle put request to /activities/:aid/update-count-emoji1 => update an existing activity count for emoji1`

`/activities/:aid/update-count-emoji2 : Handle put request to /activities/:aid/update-count-emoji2 => update an existing activity count for emoji2`

`/activities/:aid/update-count-emoji3 : Handle put request to /activities/:aid/update-count-emoji3 => update an existing activity count for emoji3`

`/activities/:aid/update-count-emoji4 : Handle put request to /activities/:aid/update-count-emoji4 => update an existing activity count for emoji4`

### Professor router: /professor-api
`/professors : Handle get request to /professors => response: a json array with all the professors from the database`

`/professors/add : Handle post request to /professors/add => add a new professor to the db`

`/professors/:pid/activites : Handle get request to /professor-api/professors/:pid/activites => response: a json array with all the activities that a professor has`

`/professors/:pid/activites/add : Handle post request to /professor-api/professors/:pid/activites/add => create an activity and bond it with a professor (professor identified by id)`

### Feedback router: /feedback-api
`/feedbacks : Handle get request to /feedbacks => response: a json array with all the feedbacks from the database`

`/feedbacks/add : Handle post request to /feedbacks/add => add a new feedback to the db`

## Dependencies used for this project
### Backend:

	npm install --save body-parser -> for parsing JSON objects

	npm i --save morgan -> for tracking any request the server is getting || the request is shown in the terminal

	npm i --save-dev nodemon -> automatically restart the server when you modify something in the files
							 -> in the package.json I added a start script "start": "nodemon server.js"
			 				 -> just type npm start and the server starts and refreshes by itself

	npm install --save express -> for using express in our project

### Frontend:
	npm i create-react-app -g

	create-react-app appname
	
	npm i @material-ui/core
	
	npm i fbemitter
	
	npm i react-router-dom    npm install react-minimal-pie-chart
	
## How to start the server
You will need to go to the project\Server-Backend file and run npm start this will start the backend server on port 8080

Any requests that come in will be shown in the console

## How to start the React-app
You will need to go the project\react-frontend file and run npm start this will start the react app on port 8081
