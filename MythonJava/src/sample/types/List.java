package sample.types;

import java.util.ArrayList;

public class List extends Sequence {

    private ArrayList<Type> types;

    public List(ArrayList<Type> types) {
        this.types = types;
    }

    public List(boolean isTemp, ArrayList<Type> types) {
        super(isTemp);
        this.types = types;
    }

    public void append(Type type) {
        this.types.add(type);
    }

    @Override
    public boolean isPrintable() {
        return true;
    }

    @Override
    public String toString() {
        if (this.types.size() == 0)
            return "[]";

        String s = "[";

        for (int i = 0; i < this.types.size() - 1; i++)
            s += this.types.get(i).toString() + ", ";
        s += this.types.get(this.types.size() - 1) + "]";
        return s;
    }

    @Override
    public String getType() {
        return "<type 'list'>";
    }

    public int len() {
        return this.types.size();
    }
}
