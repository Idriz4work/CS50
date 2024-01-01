# Hustlers Place
#### Video Demo:  <https://youtu.be/ie3zYgRGFrY?si=h3pIuVf0uvLVFu4m>
#### Description:

CS50 Final Project - Hustlers Place

My culminating project constitutes a dynamic web application crafted with Flask, designed to facilitate task management for future dates. The user experience unfolds as follows: Upon initiation, prospective users must undergo a registration process, which, upon successful completion, directs them to a personalized dashboard, herein referred to as the portfolio. This repository displays a comprehensive overview of tasks, incorporating those scheduled for the future, those accomplished in the past, and those that are pending completion.

Programming Languages and Tools Used:

HTML, CSS, and JavaScript
Python
SQL
Other small libraries and packages
Webpage Functionality:

User Registration and Login:

During registration, users must enter the following fields:
Username
Password
Confirmation (must match the entered password)
During login, users need to provide:
Username (must exist in the database)
Password (must match the password stored in the database)
Table Pages:

After registration or login, users are directed to the main page with three tables:
Tasks: Lists tasks that are yet to be completed.
Finished Tasks: Displays tasks that have been completed.
History of Tasks: Archives all tasks completed in the past.

Task Planner:
Users can input tasks in the Taskheader field, set a completion date, and provide additional details in the Task Description section.

Finish Tasks:
Users can mark tasks as finished, receive a confirmation message, and see the updated "Tasks" table on the main page.

Delete Every Tasks:
For users seeking to remove tasks from their roster, the "Delete Every Tasks" option is available. Allows users to delete all tasks in the "Tasks" table.

Delete Every Finished Tasks:
Enables users to delete all finished tasks in the "Finished Tasks" table.

Delete Memory:
Permits users to delete all finished tasks from the past stored in the "Memory" table.

Password Change
Users can enhance security and personalize their accounts by changing their passwords through the "Password" section. This process entails entering the current password and specifying a new one, reconfirming it for accuracy. Users can change their password by navigating to the "Password Change" button on the navbar. They need to enter their current password and set a new password twice. Error messages are displayed for incorrect entries.

Log Out:
To conclude a session, users can simply click on "LOG OUT" in the navigation bar, ensuring a secure disconnection from the application. This comprehensive and user-centric web application aims to streamline task management, providing a seamless and intuitive interface for users to organize and track their responsibilities efficiently. Users can log out by clicking on the "LOG OUT" button, redirecting them to the login page.

Database:
The database stores user information, tasks, finished tasks, and memory. Foreign keys are used to establish relationships between users and their login credentials.
