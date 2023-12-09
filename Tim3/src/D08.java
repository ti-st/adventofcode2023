import java.util.ArrayList;
import java.util.List;
import java.util.HashMap;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import utils.InputFile;
import utils.Utils;

class Node{
    String name;
    String[] next;
    Node(String name, String[] next){
        this.name = name;
        this.next = next;
    }
}

public class D08 {
    static List<String> raw;
    static HashMap<String, Node> nodes;
    static char[] instructions;
    static void parseInput(){
        raw = InputFile.readFile("./Tim3/src/input/08.txt");
        //raw = InputFile.readFile("./Tim3/src/input/08Sample.txt");
        //raw = InputFile.readFile("./Tim3/src/input/08SampleP2.txt");
        nodes = new HashMap<>();
        String l = raw.get(0);
        instructions = new char[l.length()];
        for (int i=0; i<l.length(); i++){
            instructions[i] = l.charAt(i);
        }
        Pattern nodePattern = Pattern.compile("(?<name>.{3}) = \\((?<left>.{3}), (?<right>.{3})\\)");
        for (String line: raw){
            Matcher matcher = nodePattern.matcher(line);
            if (matcher.find()){
                String name = matcher.group("name");
                String left = matcher.group("left");
                String right = matcher.group("right");
                String[] next = {left, right};
                Node node = new Node(name, next);
                nodes.put(name, node);
            }
        }
    }

    static int part1(){
        int steps = 0;
        Node current = nodes.get("AAA");
        while (!current.name.equals("ZZZ")){
            int idx = steps % instructions.length;
            char instruction = instructions[idx];
            if (instruction == 'L'){
                current = nodes.get(current.next[0]);
            } else if (instruction == 'R'){
                current = nodes.get(current.next[1]);
            }
            steps++;
        }
        return steps;
    }

    static int part2_bruteForce(){ // takes too long
        int steps = 0;
        List<Node> current = new ArrayList<>();
        for (Node node: nodes.values()){
            if (node.name.charAt(2) == 'A'){
                current.add(node);
            }
        }
        while(!current.stream().allMatch(i -> i.name.charAt(2) == 'Z')){
            int idx = steps % instructions.length;
            char instruction = instructions[idx];
            List<Node> next = new ArrayList<>();
            for (Node node: current){
                if (instruction == 'L'){
                    next.add(nodes.get(node.next[0]));
                } else if (instruction == 'R'){
                    next.add(nodes.get(node.next[1]));
                }
            }
            current = next;
            steps++;
            System.out.println(steps);
        }
        return steps;
    }

    static long part2(){
        HashMap<Node, Integer> nodeSteps = new HashMap<>();
        List<Node> startNodes = new ArrayList<>();
        for (Node node: nodes.values()){
            if (node.name.charAt(2) == 'A'){
                startNodes.add(node);
            }
        }
        for (Node node: startNodes){
            Node current = node;
            int steps = 0;
            while (current.name.charAt(2) != 'Z'){
                int idx = steps % instructions.length;
                char instruction = instructions[idx];
                if (instruction == 'L'){
                    current = nodes.get(current.next[0]);
                } else if (instruction == 'R'){
                    current = nodes.get(current.next[1]);
                }
                steps++;
            }
            nodeSteps.put(node, steps);
        }
        long[] allSteps = new long[nodeSteps.size()];
        int i = 0;
        for (int steps: nodeSteps.values()){
            allSteps[i] = steps;
            //System.out.println(steps);
            i++;
        }
        long result = Utils.calculateLcmOfArray(allSteps);
        return result;

    }

    public static void main(String[] args) {
        parseInput();
        System.out.println("Solution Part1: "+part1());
        System.out.println("Solution Part2: "+part2());
    }

}
