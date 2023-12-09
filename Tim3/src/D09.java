import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.stream.IntStream;

import utils.InputFile;

class OASIS{
    int[] history;
    OASIS(int[] history){
        this.history = history;
    }
    int getValue(){
        return this.getValue(this.history);
    }
    int getValue(int[] values){
        int[] diff = new int[values.length-1];
        for (int i = 0; i < values.length-1; i++) {
            diff[i] = values[i+1] - values[i];
        }
        if (IntStream.of(diff).sum() == 0) return values[values.length-1];
        else return values[values.length-1]+this.getValue(diff);
    }
    int getReverseValue(){
        return this.getReverseValue(this.history);
    }
    int getReverseValue(int[] values){
        int[] diff = new int[values.length-1];
        for (int i = 0; i < values.length-1; i++) {
            diff[i] = values[i+1] - values[i];
        }
        if (IntStream.of(diff).sum() == 0) return values[0];
        else return values[0]-this.getReverseValue(diff);
    }
    public String toString() {
        StringBuilder str = new StringBuilder();
        str.append("<");
        for (int i = 0; i < history.length; i++) {
            str.append(history[i]);
            if (i != history.length-1) str.append(", ");
        }
        str.append(">");
        return str.toString();
    }

}

public class D09 {
    static List<String> raw;
    static List<OASIS> oasises = new ArrayList<>();
    static void parseInput(){
        raw = InputFile.readFile("./Tim3/src/input/09.txt");
        //raw = InputFile.readFile("./Tim3/src/input/09Sample.txt");
        for (String line: raw){
            Pattern pattern = Pattern.compile("(-?\\d+)");
            Matcher matcher = pattern.matcher(line);
            List<Integer> numbers = new ArrayList<>();
            while (matcher.find()) {
                numbers.add(Integer.parseInt(matcher.group(1)));
            }
            int[] history = new int[numbers.size()];
            for (int i = 0; i < numbers.size(); i++) {
                history[i] = numbers.get(i);
            }
            oasises.add(new OASIS(history));
        }
        //System.out.println(oasises);
    }

    static int part1(){
        int sum = 0;
        for (OASIS oasis : oasises) {
            int v = oasis.getValue();
            sum += v;
        }
        return sum;
    }

    static int part2(){
        int sum = 0;
        for (OASIS oasis : oasises) {
            int v = oasis.getReverseValue();
            sum += v;
        }
        return sum;
    }

    public static void main(String[] args) {
        parseInput();
        System.out.println("Solution Part1: "+part1());
        System.out.println("Solution Part2: "+part2());
    }
}
