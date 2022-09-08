-- 17th Assignment. log.db is part of the Fiftyville assignment, showing SQL queries to solve the given mystery. For Specifications: https://cs50.harvard.edu/x/2022/psets/7/fiftyville/

-- Keep a log of any SQL queries you execute as you solve the mystery.
-- locate the crime scene report of the incident - hint: "the theft took place on July 28th, 2021 on Humphrey Street"
 SELECT description
   FROM crime_scene_reports
  WHERE month = 7
        AND day = 28
        AND year = 2021
        AND street = "Humphrey Street";
-- Theft of the CS50 duck took place @ 10:15AM @ Humphrey St bakery. Interviews were conducted w/3 witnesses who were present @ the time.
-- check interview logs on day of crime to locate the 3 interviews related to the crime.
 SELECT transcript
   FROM interviews
  WHERE month = 7
        AND day = 28
        AND year = 2021;
-- 1) within 10min of theft, thief drove away 2) before theft, thief withdrew money from Leggett St ATM 3) thief called someone to buy a ticket after theft for earliest flight out of Fiftyville the next day
-- find license plates around bakery within 10min of the crime
 SELECT license_plate
   FROM bakery_security_logs
  WHERE month = 7
        AND day = 28
        AND year = 2021
        AND hour = 10
        AND minute >= 15
        AND minute <= 25;
-- 5P2BI95 94KL13X 6P58WS2 4328GD8 G412CB7 L93JTIZ 322W7JE 0NTHK55
-- check ATM transactions at Leggett St ATM before crime
 SELECT account_number, amount
   FROM atm_transactions
  WHERE month = 7
        AND day = 28
        AND year = 2021
        AND atm_location = "Leggett Street"
        AND transaction_type = "withdraw";
-- 28500763/48 28296815/20 76054385/60 49610011/50 25506511/20 81061156/30 26013199/35
-- check phone calls made on date of crime
 SELECT caller, receiver
   FROM phone_calls
  WHERE month = 7
        AND day = 28
        AND year = 2021
        AND duration < 60;
-- (130) 555-0289->(996) 555-8899 (499) 555-9472->(892) 555-8872 (367) 555-5533->(375) 555-8161 (499) 555-9472->(717) 555-1342
-- (286) 555-6063->(676) 555-6554 (770) 555-1861->(725) 555-3243 (031) 555-6622->(910) 555-3251 (826) 555-1652->(066) 555-9701 (339) 555-6650 -> (704) 555-2131
-- check bank account ownership of withdrawals
 SELECT person_id
   FROM bank_accounts
  WHERE account_number = 28500763
        OR account_number = 28296815
        OR account_number = 76054385
        OR account_number = 49610011
        OR account_number = 25506511
        OR account_number = 81061156
        OR account_number = 26013199;
-- 686048 514354 395717 396669 449774 438727
-- check phone numbers and license plates of these individuals
 SELECT name, phone_number, license_plate, passport_number
   FROM people
  WHERE id = 686048
        OR id = 514354
        OR id = 395717
        OR id = 396669
        OR id = 449774
        OR id = 438727;
-- Kenny (826) 555-1652 30G67EN Iman (829) 555-5269 L93JTIZ Benista (338) 555-6650 8X428L0 Taylor (286) 555-6063 1106N58 Diana (770) 555-1861 322W7JE Bruce (367) 555-5533 94KL13X
-- Diana (3592750733), Bruce (5773259633) license plates were at scene and are phone callers on day of crime
-- find Fiftyville airport
 SELECT full_name, abbreviation, id
   FROM airports
  WHERE city = "Fiftyville";
-- Fiftyville Regional Airport / CSF / 8
-- Find earliest flight out of Fiftyville
 SELECT id, hour, minute
   FROM flights
  WHERE month = 7
        AND day = 29
        AND year = 2021
        AND origin_airport_id = 8;
-- earliest flight from Fiftyville is 8:20AM, ID 36
-- see if Diana or Bruce are on plane by matching passport ID
SELECT passport_number
  FROM passengers
 WHERE flight_id = 36;
 -- Bruce's passport number is a match
 -- find Bruce's destination
SELECT city
  FROM airports
 WHERE id =
       (SELECT destination_airport_id
          FROM flights
         WHERE id = 36);
-- New York City
-- find Bruce's accomplice
SELECT name
  FROM people
 WHERE phone_number = "(375) 555-8161";
 -- Robin is Bruce's accomplice
