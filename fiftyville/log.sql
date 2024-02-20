-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT description FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28;

SELECT transcript FROM interviews WHERE day = 28 AND month = 7 AND year = 2021 AND transcript like "%bakery%";

SELECT name FROM people JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10 AND minute >= 15 AND minute < 25 AND activity = "exit";

SELECT DISTINCT name FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number WHERE day = "28" AND month = "7" AND year = "2020" AND transaction_type = "withdraw" AND atm_location = "Humphrey Street";

