-- Keep a log of any SQL queries you execute as you solve the mystery.

-- QUERY 1
--Get initial report information at the specified date and location
SELECT description FROM crime_scene_reports WHERE street='Chamberlin Street' AND year=2020 AND day=28 AND month=07;

--Result
-- Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
-- Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.

-- QUERY 2
-- Get interviews
 SELECT id,name,transcript FROM interviews WHERE day=28 AND month=07 AND year=2020;

-- Result
-- id | name | transcript
-- 158 | Jose | “Ah,” said he, “I forgot that I had not seen you for some weeks. It is a little souvenir from the King of Bohemia in return for my assistance in the case of the Irene Adler papers.”

-- 159 | Eugene | “I suppose,” said Holmes, “that when Mr. Windibank came back from France he was very annoyed at your having gone to the ball.”

-- 160 | Barbara | “You had my note?” he asked with a deep harsh voice and a strongly marked German accent. “I told you that I would call.”
--                  He looked from one to the other of us, as if uncertain which to address.

-- 161 | Ruth | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away.
--              If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.

-- 162 | Eugene | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse,
--                I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.

-- 163 | Raymond | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute.
--                 In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
--                 The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- QUERY 3
-- Check logs at the courhouse within 10 minutes of the theft (from 10:15 AM to 10:25 AM)
SELECT id, activity, license_plate, hour, minute FROM courthouse_security_logs WHERE day=28 AND month=07 AND year=2020 AND hour=10 AND minute>=15 AND minute <=25;
-- id | activity | license_plate | hour | minute
-- 260 | exit | 5P2BI95 | 10 | 16
-- 261 | exit | 94KL13X | 10 | 18
-- 262 | exit | 6P58WS2 | 10 | 18
-- 263 | exit | 4328GD8 | 10 | 19
-- 264 | exit | G412CB7 | 10 | 20
-- 265 | exit | L93JTIZ | 10 | 21
-- 266 | exit | 322W7JE | 10 | 23
-- 267 | exit | 0NTHK55 | 10 | 23

-- QUERY 4
-- Find the earliest flight on July 29th 2020, which the thief used to escape.
SELECT flights.id AS flight_id, d.id AS destination_ID,d.city FROM flights JOIN airports d  ON (flights.destination_airport_id = d.id) JOIN airports o ON (flights.origin_airport_id=o.id)
WHERE o.city='Fiftyville' AND year=2020 AND day=29 AND month=07 ORDER BY hour ASC, minute ASC LIMIT 1;
-- flight_id | destination_ID | city
-- 36        | 4              | London
-- Thief escaped to London!

-- QUERY 5
-- Get passengers in the escape flight that have a license plate that exited the courthouse from 10:15 to 10:25 AM
SELECT p.name, p.license_plate FROM people p JOIN passengers pa ON (p.passport_number = pa.passport_number) JOIN flights f ON (f.id=pa.flight_id) WHERE pa.flight_id=36
AND p.license_plate IN (SELECT csl.license_plate FROM courthouse_security_logs csl WHERE day=28 AND month=07 AND year=2020 AND hour=10 AND minute>=15 AND minute <=25);
-- name     | license_plate
-- Roger    | G412CB7
-- Ernest   | 94KL13X
-- Evelyn   | 0NTHK55
-- Danielle | 4328GD8

-- QUERY 6
-- Who used the ATM at Fifer Street to withdraw on the day of the theft?
SELECT p.name FROM atm_transactions at JOIN bank_accounts ba ON (at.account_number = ba.account_number) JOIN people p ON (p.id = ba.person_id)
WHERE at.day=28 AND at.month=7 AND at.year=2020 AND at.transaction_type='withdraw' AND at.atm_location='Fifer Street';
-- name
-- Ernest
-- Russell
-- Roy
-- Bobby
-- Elizabeth
-- Danielle
-- Madison
-- Victoria

-- QUERY 7
-- Combine queries 5 and 6 to narrow down options
SELECT p.name FROM atm_transactions at JOIN bank_accounts ba ON (at.account_number = ba.account_number) JOIN people p ON (p.id = ba.person_id)
WHERE at.day=28 AND at.month=7 AND at.year=2020 AND at.transaction_type='withdraw' AND at.atm_location='Fifer Street' AND p.name IN
(SELECT p2.name FROM people p2 JOIN passengers pa ON (p2.passport_number = pa.passport_number) JOIN flights f ON (f.id=pa.flight_id) WHERE pa.flight_id=36
AND p.license_plate IN (SELECT csl.license_plate FROM courthouse_security_logs csl WHERE day=28 AND month=07 AND year=2020 AND hour=10 AND minute>=15 AND minute <=25));
-- name
-- Ernest
-- Danielle

-- QUERY 8
-- Get the times Danielle and Ernest left the courthouse
SELECT p.name, csl.activity, csl.license_plate, csl.hour, csl.minute FROM courthouse_security_logs csl JOIN people p ON (csl.license_plate = p.license_plate)
WHERE csl.day=28 AND csl.month=07 AND csl.year=2020 AND csl.hour=10 AND csl.minute>=15 AND csl.minute <=25 AND (p.name='Danielle' OR p.name='Ernest');
-- name     | activity | license_plate | hour | minute
-- Ernest   | exit     | 94KL13X       |  10  | 18
-- Danielle | exit     | 4328GD8       |  10  | 19

-- QUERY 9
-- Check for calls that lasted less than 1 minute (<60 seconds)!
SELECT caller, receiver FROM phone_calls WHERE day=28 AND month=07 AND year=2020 AND duration<60;
--      caller    |    receiver
-- (130) 555-0289 | (996) 555-8899
-- (499) 555-9472 | (892) 555-8872
-- (367) 555-5533 | (375) 555-8161
-- (499) 555-9472 | (717) 555-1342
-- (286) 555-6063 | (676) 555-6554
-- (770) 555-1861 | (725) 555-3243
-- (031) 555-6622 | (910) 555-3251
-- (826) 555-1652 | (066) 555-9701
-- (338) 555-6650 | (704) 555-2131

-- QUERY 10
-- Check the name of the callers from previous entry - thief is among them!
SELECT name FROM people p JOIN phone_calls pc ON (pc.caller = p.phone_number) WHERE pc.day=28 AND pc.month=07 AND pc.year=2020 AND pc.duration<60;
-- name
-- Roger
-- Evelyn
-- Ernest
-- Evelyn
-- Madison
-- Russell
-- Kimberly
-- Bobby
-- The Thief is Ernest! We had already narrowed down to either Ernest or Danielle from Query 8 and only Ernest showed up in Query 10!

-- QUERY 11
-- Check the name of the receiver from Ernest's call - the accomplice!
SELECT r.name FROM people r JOIN phone_calls pc ON (pc.receiver = r.phone_number) JOIN people c ON (pc.caller = c.phone_number)
WHERE pc.day=28 AND pc.month=07 AND pc.year=2020 AND pc.duration<60 AND c.name='Ernest';
-- name
-- Berthold
-- Berthold is the accomplice!