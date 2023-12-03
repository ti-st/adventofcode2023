      * day3_1
       identification division.
           program-id. engine_parts.
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
           01 input_line pic x(140).

           working-storage section.

           01 p-index pic 9(9).
           01 i-index pic 9(9).

           01 schematic_nums.
               02 part_number occurs 10000 times.
                   03 part pic 9(5).
                   03 p-line_number pic 9(4).
                   03 p-start_index pic 9(3).
                   03 p-end_index pic 9(3).
                   03 p-in-sum pic 9.

           01 schematic_indicator.
               02 indicator occurs 10000 times.
                   03 in-line_number pic 9(4).
                   03 in-index pic 9(3).


           01 curr_num pic 9(4).
           01 ws-i pic 9(9).
           01 ws-j pic 9(9).
           01 ws-k pic 9(9).

           01 look_up_x pic 9(9).
           01 look_up_y pic 9(9).

           01 loop_up_r pic 9(5).

           01 ws-num_found pic 9(1).

           01 ws-curr_line_num pic 9(9).


           01 ws-sum pic 9(10).
           01 ws-eof pic a(1).

       procedure division.

           move 1 to p-index.
           move 1 to i-index.
           move 1 to ws-curr_line_num.

           open input f-input.
           perform until ws-eof = 'Y'
               read f-input into input_line at
               end move 'Y' to ws-eof
               not at end

      *             display input_line
                   perform load_schematic


               add 1 to ws-curr_line_num

           end-perform.

           perform look_for_valid_parts.

           display "sum " ws-sum.
           close f-input.
           stop run.

       load_schematic.

           move 0 to curr_num.
           move 0 to ws-num_found.

           perform varying ws-i from 1 by 1
               until ws-i > function length(input_line)

      *         display ws-i

               if input_line(ws-i:1) is numeric then
      *             display input_line(ws-i:1) " line "
      *                ws-curr_line_num " index "ws-i
                   move function numval(input_line(ws-i:1)) to ws-k
                   if ws-num_found = 1 then
                       compute curr_num = curr_num * 10 + ws-k
                   else
                       move ws-i to p-start_index(p-index)
                       move ws-k to curr_num
                   end-if
                   move 1 to ws-num_found
               else
                   if ws-num_found = 1 then
                       move ws-i to p-end_index(p-index)
                       subtract 1 from p-end_index(p-index)
                       move ws-curr_line_num to p-line_number(p-index)
                       move curr_num to part(p-index)
                       move 0 to p-in-sum(p-index)
      *                 display part_number(p-index)
                       add 1 to p-index
                   end-if
                   move 0 to curr_num
                   move 0 to ws-num_found
               end-if

               if input_line(ws-i:1) not numeric
                   and input_line(ws-i:1) not = '.' then

                   move ws-curr_line_num to in-line_number(i-index)
                   move ws-i to in-index(i-index)
      *             display indicator(i-index)
                   add 1 to i-index

               end-if
           end-perform.

           if ws-num_found = 1 then
               move ws-i to p-end_index(p-index)
               subtract 1 from p-end_index(p-index)
               move ws-curr_line_num to p-line_number(p-index)
               move curr_num to part(p-index)
               move 0 to p-in-sum(p-index)
      *         display part_number(p-index)
               add 1 to p-index
           end-if.
           move 0 to curr_num.
           move 0 to ws-num_found.



       look_for_valid_parts.

           perform varying ws-i from 1 by 1 until ws-i > p-index

      *         display "look on indexer "
      *         in-index(ws-i) " " in-line_number(ws-i)
      *top
               compute look_up_x = in-index(ws-i)
               compute look_up_y = in-line_number(ws-i) - 1
               perform look_up_part
               add loop_up_r to ws-sum

      *top-right
               compute look_up_x = in-index(ws-i) + 1
               compute look_up_y = in-line_number(ws-i) - 1
               perform look_up_part
               add loop_up_r to ws-sum
      *right
               compute look_up_x = in-index(ws-i) + 1
               compute look_up_y = in-line_number(ws-i)
               perform look_up_part
               add loop_up_r to ws-sum
      *bottom-right
               compute look_up_x = in-index(ws-i) + 1
               compute look_up_y = in-line_number(ws-i) + 1
               perform look_up_part
               add loop_up_r to ws-sum
      *bottom
               compute look_up_x = in-index(ws-i)
               compute look_up_y = in-line_number(ws-i) + 1
               perform look_up_part
               add loop_up_r to ws-sum
      *bottom-left
               compute look_up_x = in-index(ws-i) - 1
               compute look_up_y = in-line_number(ws-i) + 1
               perform look_up_part
               add loop_up_r to ws-sum
      *left
               compute look_up_x = in-index(ws-i) - 1
               compute look_up_y = in-line_number(ws-i)
               perform look_up_part
              add loop_up_r to ws-sum
      *top-left
               compute look_up_x = in-index(ws-i) - 1
               compute look_up_y = in-line_number(ws-i) - 1
               perform look_up_part
               add loop_up_r to ws-sum

           end-perform.

       look_up_part.

           move 0 to loop_up_r.

           if look_up_x > 0
               and look_up_y > 0
               and look_up_x < function length(input_line)
               and look_up_y < ws-curr_line_num + 1 then

               perform varying ws-j from 1 by 1 until ws-j > p-index

                   if look_up_y = p-line_number(ws-j)
                       and look_up_x >= p-start_index(ws-j)
                       and look_up_x <= p-end_index(ws-j)
                       and p-in-sum(ws-j) = 0 then
                       move part(ws-j) to loop_up_r
                       move 1 to p-in-sum(ws-j)
      *                 display  part(ws-j)
      *                     " found on " look_up_x " " look_up_y
                       exit paragraph
                   end-if

               end-perform
           end-if.
