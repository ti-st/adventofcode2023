      * day4_1
       identification division.
           program-id. scratchcards.
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

           01 ws-i pic 9(9).
           01 ws-j pic 9(9).

           01 ws-curr_winnigs pic 9(9).
           01 ws-found-one pic 9.

           01 ws-sum pic 9(10).
           01 ws-eof pic a(1).

       procedure division.

           open input f-input.
           perform until ws-eof = 'Y'
               read f-input into input_line at
               end move 'Y' to ws-eof
               not at end
               move 1 to ws-curr_winnigs
               move 0 to ws-found-one
      *         display y-num(1)
               perform look_for_winnings
               if ws-found-one = 1 then
                   compute ws-curr_winnigs = ws-curr_winnigs / 2
                   add ws-curr_winnigs to ws-sum
                   display cardNr " worth " ws-curr_winnigs " points"
               end-if

           end-perform.

           display "sum " ws-sum.
           close f-input.
           stop run.

       look_for_winnings.
           perform varying ws-i from 1 by 1
               until ws-i > 10

               perform varying ws-j from 1 by 1 until
                   ws-j > 25

                   if y-num(ws-i) = w-num(ws-j) then
                       compute ws-curr_winnigs = ws-curr_winnigs * 2
                       move 1 to ws-found-one
                   end-if
               end-perform

           end-perform.
