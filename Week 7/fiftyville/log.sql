-- Keep a log of any SQL queries you execute as you solve the mystery.
-- The CS50 Duck has been stolen! The town of Fiftyville has called upon you to solve the mystery of the stolen duck.
-- Authorities believe that the thief stole the duck and then, shortly afterwards,
-- took a flight out of town with the help of an accomplice. Your goal is to identify:
--      • Who the thief is,
--      • What city the thief escaped to, and
--      • Who the thief’s accomplice is who helped them escape
-- All you know is that the theft took place on July 28, 2021 and that it took place on Humphrey Street.



-- crime_scene_reports
SELECT id, description
FROM crime_scene_reports
WHERE year = 2021 AND month = 7 AND day = 28 AND street = 'Humphrey Street';
--      • Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
--      • Interviews were conducted today with three witnesses who were present at the time –
--      each of their interview transcripts mentions the bakery.
-- interviews
SELECT id, transcript
FROM interviews
WHERE year = 2021 AND month = 7 AND day = 28;
--      • Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
--      • Earlier this morning, before I arrived at Emma's bakery,
--      I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
--      • As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
--      In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
--      The thief then asked the person on the other end of the phone to purchase the flight ticket.



-- IDENTITY OF THE THIEF
-- Find out the thief by getting all the names that has:
--      • transaction within the day from Leggett Street
--      • phone call within the day and lasted less than a minute (60)
--      • exited within 10 mins after 10:15 AM theft from the bakery.
--      • has a flight tomorrow (July 29, 2021) from Fiftyville
SELECT people.name AS Suspect
FROM people JOIN bank_accounts
ON people.id = bank_accounts.person_id
WHERE bank_accounts.account_number IN
(
    SELECT account_number
    FROM atm_transactions
    WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'
)
AND people.phone_number IN
(
    SELECT caller
    FROM phone_calls
    WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60
)
AND people.license_plate IN
(
    SELECT license_plate
    FROM bakery_security_logs
    WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND (minute >= 15 OR minute <= 25) AND activity = 'exit'
)
AND people.passport_number IN
(
    SELECT passport_number
    FROM passengers
    WHERE flight_id IN
    (
        SELECT id
        FROM flights
        WHERE year = 2021 AND month = 7 AND day = 29
        AND origin_airport_id IN
        (
            SELECT id
            FROM airports
            WHERE city = 'Fiftyville'
        )
    )
)
;
-- Suspect:
-- • Bruce
-- • Diana
-- • Taylor

-- Confirm the suspect by checking the activities of the suspect's accomplice
SELECT people.name as Accomplice
FROM people JOIN phone_calls
ON people.phone_number = phone_calls.receiver
WHERE phone_calls.duration < 60
AND phone_calls.caller IN
(
    SELECT phone_number
    FROM people
    WHERE (name = 'Bruce' OR name = 'Diana' OR name = 'Taylor')
)
;
-- Accomplice:
-- • Robin
-- • James
-- • Philip
-- • Charlotte

-- Bruce is the most likely thief and Robin as their accomplice.

-- DESTINATION
SELECT full_name, city
FROM airports
WHERE id IN
(
    SELECT destination_airport_id
    FROM flights JOIN passengers
    ON flights.id = passengers.flight_id
    WHERE flights.year = 2021 AND flights.month = 7 AND flights.day = 29
    AND passengers.passport_number IN
    (
        SELECT passport_number
        FROM people
        WHERE name = 'Bruce'
    )
    AND flights.origin_airport_id IN
    (
        SELECT id
        FROM airports
        WHERE city = 'Fiftyville'
    )
)
;

-- Bruce escaped to New York City.