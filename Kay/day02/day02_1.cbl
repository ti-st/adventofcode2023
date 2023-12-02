      * day1_1
       identification division.
           program-id. elf_game.
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
           01 input_line pic x(200).

           working-storage section.

           01 ws-f_split.
               02 ws-game_id_split pic x(200)
               occurs 2 times indexed by j.
               02 ws-game_play_split pic x(50)
               occurs 30 times.

           01 ws-temp_str pic x(200).

           01 ws-game.
               02 ws-game_id pic 9(9).
               02 rounds occurs 30 times indexed by i.
                   03 blues pic 9(9).
                   03 reds pic 9(9).
                   03 greens pic 9(9).

           01 ws-cube_indentify pic x(10).
               88 isBlue value "blue".
               88 isRed value "red".
               88 isGreen value "green".

           01 ws-i pic 9(9).
           01 ws-j pic 9(9).
           01 ws-k pic 9(9).
           01 ws-l pic 9(9).
           01 ws-inval pic 9(1).

           01 ws-sub pic 9(9).
           01 ws-start pic 9(9).
           01 ws-index pic 9(9).

           01 ws-nr pic 9(9).

           01 ws-red_max pic 9(9).
           01 ws-green_max pic 9(9).
           01 ws-blue_max pic 9(9).

           01 ws-eof pic a(1).

           01 ws-sum pic 9(9).

           01 ws-blue_high pic 9(9).
           01 ws-red_high pic 9(9).
           01 ws-green_high pic 9(9).

           01 ws-sum-ext pic 9(9).

       procedure division.

           move 12 to ws-red_max.
           move 13 to ws-green_max.
           move 14 to ws-blue_max.

           move 0 to ws-sum.

           open input f-input.
           perform until ws-eof = 'Y'
               read f-input into input_line at
               end move 'Y' to ws-eof
               not at end

               perform tran_line

           end-perform.
           display "sum " ws-sum.
           display "sum ext" ws-sum-ext.
           close f-input.
           stop run.

       tran_line.
      *    split gamevesion and game play
           move 0 to ws-i.
           inspect input_line tallying ws-i for characters before ':'.
           move input_line(1:ws-i) to ws-game_id_split(1).
           add 3 to ws-i.
           move input_line(ws-i:180) to ws-game_id_split(2).
      *     display  ws-game_id_split(1).
      *     display ws-game_id_split(2).

           move function numval(ws-game_id_split(1)(5:7)) to ws-game_id.

           display ws-game_id.

           move 0 to ws-sub.
           move 1 to ws-start.
           move 0 to ws-index.
           move 0 to ws-i.

           perform varying ws-k from 1 by 1 until ws-k > 30
               move 0 to blues(ws-k)
               move 0 to reds(ws-k)
               move 0 to greens(ws-k)
           end-perform.

           move 0 to ws-k.

           perform varying ws-sub
               from 1 by 1
               until ws-sub > function length(ws-game_id_split(2))
               if ws-game_id_split(2)(ws-sub:1) = ';' then
                   add 1 to ws-index

                   compute ws-i = ws-sub - ws-start

                   move  ws-game_id_split(2)(ws-start:ws-i)
                       to ws-game_play_split(ws-index)

                   compute ws-start = ws-sub + 1

                end-if
           end-perform.

           add 1 to ws-index.
           compute ws-i = ws-sub - ws-start.
           move  ws-game_id_split(2)(ws-start:ws-i)
               to ws-game_play_split(ws-index).


           move ws-index to ws-j.
           move 0 to ws-i.


           perform varying ws-i from 1 by 1 until ws-i > ws-j

               move 0 to ws-sub
               move 1 to ws-start
               move 0 to ws-index
               move 0 to ws-k

      *         display ws-game_play_split(ws-i)
               perform varying ws-sub from 1 by 1
                   until ws-sub > function length(ws-game_play_split(1))

                   if ws-game_play_split(ws-i)(ws-sub:1) = ',' then
                       perform inter_game_index
                   end-if

               end-perform
              perform inter_game_index

               display rounds(ws-i)
           end-perform.
           perform check_round.


       inter_game_index.
           add 1 to ws-index.

           compute ws-k = ws-sub - ws-start.
           move ws-game_play_split(ws-i)(ws-start:ws-k)
               to ws-temp_str.
           compute ws-start = ws-sub + 1.
           move function trim(ws-temp_str) to ws-temp_str.

           move 0 to ws-l.
           inspect ws-temp_str tallying ws-l
               for characters before space.
           add 1 to ws-l.
      *    display function trim(ws-temp_str(ws-l:6)).

           move function trim(ws-temp_str(ws-l:6)) to ws-cube_indentify.
           evaluate true
               when isBlue move
                   function numval(ws-temp_str(1:ws-l)) to blues(ws-i)
               when isRed move
                   function numval(ws-temp_str(1:ws-l)) to reds(ws-i)
               when isGreen move
                   function numval(ws-temp_str(1:ws-l)) to greens(ws-i)
           end-evaluate.


       check_round.
           move 1 to ws-i.
           move 0 to ws-inval.
           display "check"


           perform varying ws-i from 1 by 1
               until ws-i > 30

      *         display rounds(ws-i)

               if blues(ws-i) > ws-blue_max
                   or reds(ws-i) > ws-red_max
                   or greens(ws-i) > ws-green_max then
                   display "game " ws-game_id " invalid"
                   move 1 to ws-inval
                   move 31 to ws-i
               end-if

           end-perform.

           if ws-inval = 0 then
               add ws-game_id to ws-sum
           end-if.

           move 0 to ws-blue_high.
           move 0 to ws-green_high.
           move 0 to ws-red_high.

           perform varying ws-i from 1 by 1
               until ws-i > 30

               if blues(ws-i) > ws-blue_high then
                   move blues(ws-i) to ws-blue_high
               end-if
               if reds(ws-i) > ws-red_high then
                   move reds(ws-i) to ws-red_high
               end-if
               if greens(ws-i) > ws-green_high then
                   move greens(ws-i) to ws-green_high
               end-if
           end-perform.

           compute ws-sum-ext
               = ws-sum-ext
               + (ws-blue_high * ws-red_high * ws-green_high).