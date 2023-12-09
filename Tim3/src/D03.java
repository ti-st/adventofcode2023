import java.util.ArrayList;
import java.util.List;

import utils.InputFile;

class Part{
    int nr;
    int digits;
    int x;
    int y;
    List<Symbol> symbols;
    Part(int nr){
        this.nr = nr;
        this.digits = 1;
        this.symbols = new ArrayList<>();
    }
    public void addDigit(int digit){
        this.digits++;
        this.nr = this.nr*10 + digit;
    }
    public void addSymbol(Symbol symbol){
        this.symbols.add(symbol);
    }
    public boolean isAdjacent(int x, int y){
        for (int i=0; i<this.digits; i++){
            if (Math.abs(this.x+i-x) <= 1 && Math.abs(this.y-y) <= 1){
                return true;
            }
        }
        return false;
    }
}

class Symbol{
    int x;
    int y;
    char symbol;
    List<Part> parts;
    Symbol(int x, int y, char symbol){
        this.x = x;
        this.y = y;
        this.symbol = symbol;
        this.parts = new ArrayList<>();
    }
}

public class D03 {
    public static void main(String[] args) {
        List<String> raw = InputFile.readFile("./Tim3/src/input/03.txt");
        //List<String> raw = InputFile.readFile("./Tim3/src/input/03Sample.txt");
        List<Part> parts = new ArrayList<>();
        List<Symbol> symbols = new ArrayList<>();
        for (int l_i=0; l_i<raw.size(); l_i++){
            String line = raw.get(l_i);
            Part curr_part = null;
            for (int c_i=0; c_i<line.length(); c_i++){
                char c = line.charAt(c_i);
                if (Character.isDigit(c)){
                    if (curr_part != null){
                        curr_part.addDigit(Character.getNumericValue(c));
                    }else{
                        curr_part = new Part(Character.getNumericValue(c));
                        curr_part.x = c_i;
                        curr_part.y = l_i;
                    }
                }else {
                    if (curr_part != null){
                        parts.add(curr_part);
                    }
                    curr_part = null;
                    if(c != '.'){
                        symbols.add(new Symbol(c_i, l_i, c));
                    }
                }
            }
            if (curr_part != null){
                parts.add(curr_part);
            }
        }

        int p1_sum = 0;
        for (Part part : parts) {
            for (Symbol symbol : symbols) {
                if (part.isAdjacent(symbol.x, symbol.y)){
                    part.addSymbol(symbol);
                    if (part.symbols.size() == 1){
                        p1_sum += part.nr;
                        //System.out.println(part.nr +" " + symbol.symbol);
                    }
                    symbol.parts.add(part);
                }
            }
        }
        System.out.println("Part 1: " + p1_sum);

        int p2_sum = 0;
        for (Symbol symbol : symbols) {
            if (symbol.symbol != '*') continue;
            if (symbol.parts.size() == 2){
                p2_sum += symbol.parts.get(0).nr*symbol.parts.get(1).nr;
            }
        }
        System.out.println("Part 2: " + p2_sum);

    }

}
