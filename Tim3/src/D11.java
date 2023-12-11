import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import utils.InputFile;
import utils.Utils;

class Space{
    int x;
    int y;
    char type;
    int id;
    Space(int x, int y, char type, int id){
        this.x = x;
        this.y = y;
        this.type = type;
        this.id = id;
    }
}

public class D11{
    static List<String> raw;
    static List<List<Space>> rawGrid;
    static List<List<Character>> grid;
    static List<List<Space>> spaceGrid;
    static void parseInput(){
        raw = InputFile.readFile("./Tim3/src/input/11.txt");
        raw = InputFile.readFile("./Tim3/src/input/11Sample.txt");
        grid = new ArrayList<>();
        for(String s: raw){
            List<Character> row = new ArrayList<>();
            boolean allEmpty = true;
            for(char c: s.toCharArray()){
                row.add(c);
                if (c != '.'){
                    allEmpty = false;
                }
            }
            grid.add(row);
            //add extra row if all empty
            if (allEmpty){
                grid.add(new ArrayList<Character>(row));
            }

        }
        List<List<Character>> tmp = Utils.transpose(grid);
        //printGrid(tmp);
        for (int i = 0; i<tmp.size(); i++){
            boolean allEmpty = true;
            for (char c: tmp.get(i)){
                if (c != '.'){
                    allEmpty = false;
                }
            }
            if (allEmpty){
                tmp.add(i, new ArrayList<>(tmp.get(i)));
                i++;
            }
        }
        grid = Utils.transpose(tmp);
        //printGrid(grid);

        spaceGrid = new ArrayList<>();
        int gc = 1;
        for (int i = 0; i<grid.size(); i++){
            List<Space> row = new ArrayList<>();
            for (int j = 0; j<grid.get(i).size(); j++){
                int id = 0;
                if (grid.get(i).get(j) != '.'){
                    id = gc;
                    gc++;
                }
                row.add(new Space(j, i, grid.get(i).get(j), id));
            }
            spaceGrid.add(row);
        }

        //p2
        rawGrid = new ArrayList<>();
        gc = 1;
        for (int i = 0; i<raw.size(); i++){
            List<Space> row = new ArrayList<>();
            String s = raw.get(i);
            for (int j = 0; j<s.length(); j++){
                int id = 0;
                if (s.charAt(j) != '.') id = gc++;
                row.add(new Space(j, i, s.charAt(j), id));
            }
            rawGrid.add(row);
        }
    }

    static void printGrid(List<List<Character>> grid){
        for(List<Character> row: grid){
            for(char c: row){
                System.out.print(c);
            }
            System.out.println();
        }
    }
    static void printSpaceGrid(List<List<Space>> grid){
        for(List<Space> row: grid){
            for(Space s: row){
                if (s.type == '.') System.out.print('.');
                else System.out.print(s.id);
            }
            System.out.println();
        }
    }

    static int part1(){
        List<Space> galaxies = new ArrayList<>();
        for (List<Space> row: spaceGrid){
            for (Space space: row){
                if (space.type == '.') continue;
                galaxies.add(space);
            }
        }
        HashMap<Space, List<Space>> visited = new HashMap<>();
        int distSum = 0;
        for (Space galaxy: galaxies){
            visited.put(galaxy, new ArrayList<>());
            for (Space other: galaxies){
                if (galaxy == other) continue;
                if (visited.containsKey(other) && visited.get(other).contains(galaxy)) continue;
                visited.get(galaxy).add(other);
                int dist = Math.abs(galaxy.x - other.x) + Math.abs(galaxy.y - other.y);
                distSum += dist;
                //System.out.println(galaxy.id + " - " + other.id + " : " + dist);
            }
        }
        return distSum;
    }

    static int part2(){
        List<Integer> emptyCols = new ArrayList<>();
        List<Integer> emptyRows = new ArrayList<>();
        for (int i = 0; i<rawGrid.size(); i++){
            boolean allEmpty = true;
            for (Space s: rawGrid.get(i)){
                if (s.type != '.'){
                    allEmpty = false;
                    break;
                }
            }
            if (allEmpty){
                emptyRows.add(i);
            }
        }
        for (int i = 0; i<rawGrid.get(0).size(); i++){
            boolean allEmpty = true;
            for (List<Space> row: rawGrid){
                if (row.get(i).type != '.'){
                    allEmpty = false;
                    break;
                }
            }
            if (allEmpty){
                emptyCols.add(i);
            }
        }
        List<Space> galaxies = new ArrayList<>();
        for (List<Space> row: spaceGrid){
            for (Space space: row){
                if (space.type == '.') continue;
                galaxies.add(space);
            }
        }

        HashMap<Space, List<Space>> visited = new HashMap<>();
        int distSum = 0;
        for (Space galaxy: galaxies){
            visited.put(galaxy, new ArrayList<>());
            for (Space other: galaxies){
                if (galaxy == other) continue;
                if (visited.containsKey(other) && visited.get(other).contains(galaxy)) continue;
                visited.get(galaxy).add(other);
                int bx,by, sx,sy;
                if (galaxy.x > other.x){
                    bx = galaxy.x;
                    sx = other.x;
                } else {
                    bx = other.x;
                    sx = galaxy.x;
                }
                if (galaxy.y > other.y){
                    by = galaxy.y;
                    sy = other.y;
                } else {
                    by = other.y;
                    sy = galaxy.y;
                }
                int ecols = 0;
                for (int i=sx; i<bx; i++){
                    if (emptyCols.contains(i)){
                        ecols++;
                    }
                }
                int erows = 0;
                for (int i=sy; i<by; i++){
                    if (emptyRows.contains(i)){
                        erows++;
                    }
                }
                bx = bx+10*ecols;
                by = by+10*erows;
                int dist = Math.abs(bx - sx) + Math.abs(by - sy);
                //int dist = Math.abs(galaxy.x - other.x) + Math.abs(galaxy.y - other.y);
                distSum += dist;
                //System.out.println(galaxy.id + " - " + other.id + " : " + dist);
            }
        }

        return distSum;
    }

    public static void main(String[] args) {
        parseInput();
        //printGrid(grid);
        System.out.println(part1());
        //System.out.println(part2());
    }
}
