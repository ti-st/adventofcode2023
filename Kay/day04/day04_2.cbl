      * day4_1
       identification division.
           program-id. scratchcards_real_winnings.
           author. kayms.
      *
       environment division.
           input-output section.
           file-control.
           select f-input assign to "../input.txt"
           organization is line sequential.

       data division.
           file section.

           fd f-input.
           01 input_line.
               02 filler pic x(5).
               02 cardNr pic 999.
               02 filler pic x.
               02 y-num pic 999 occurs 10 times.
               02 filler pic xx.
               02 w-num pic 999 occurs 25 times.

           working-storage section.

           01 ws-cards.
               02 ws-card_nr pic 999 occurs 300 times.
               02 ws-card_score pic 999 occurs 300 times.
               02 ws-instances pic 9(9) occurs  300 times.
               02 ws-card_curr_index pic 9(9) occurs  300 times.

           01 ws-i pic 9(9).
           01 ws-j pic 9(9).
           01 ws-k pic 9(9).

           01 ws-curr_winnigs pic 9(9).
           01 ws-found-one pic 9.
           01 ws-temp pic 9(9).

           01 ws-sum pic 9(10).
           01 ws-eof pic a(1).

       procedure division.

           open input f-input.
           perform until ws-eof = 'Y'
               read f-input into input_line at
               end move 'Y' to ws-eof
               not at end
               display cardNr
               move 1 to ws-curr_winnigs
               move 0 to ws-found-one

               move function numval(cardNr) to cardNr
               move cardNr to ws-card_nr(cardNr)
               move 1 to ws-instances(cardNr)
               move 0 to ws-card_score(cardNr)
               move 1 to ws-card_curr_index(cardNr)

               display cardNr
               perform look_for_winnings

               if ws-found-one = 1 then
                   compute ws-curr_winnigs = ws-curr_winnigs - 1
                   move ws-curr_winnigs to ws-card_score(cardNr)
               end-if

               display cardNr " score " ws-card_score(cardNr)


           end-perform.


           move 1 to ws-i.
           perform calc_cards_winnings.


           perform varying ws-i from 1 by 1 until ws-i > 200
               display "card "ws-i " instances " ws-instances(ws-i)
               add ws-instances(ws-i) to ws-sum
           end-perform.

           display "sum " ws-sum.
           close f-input.
           stop run.

       look_for_winnings.
           perform varying ws-i from 1 by 1
               until ws-i > 10

               perform varying ws-j from 1 by 1 until ws-j > 25

                   if y-num(ws-i) = w-num(ws-j) then
                       compute ws-curr_winnigs = ws-curr_winnigs + 1
                       move 1 to ws-found-one
                   end-if
               end-perform

           end-perform.

       calc_cards_winnings.
           perform varying ws-i from 1 by 1 until ws-i > 200
      *         display "card " ws-i " score " ws-card_score(ws-i)
               perform varying ws-j from 1 by 1
                   until ws-j > ws-card_score(ws-i)

                   perform varying ws-k from 1 by 1
                       until ws-k > ws-instances(ws-i)
                           compute ws-temp = ws-i + ws-j
      *                     display " copy of "ws-temp
                           add 1 to ws-instances(ws-temp)
                   end-perform
               end-perform
           end-perform.