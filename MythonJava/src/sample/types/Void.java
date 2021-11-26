package sample.types;

public class Void extends Type {
    @Override
    public boolean isPrintable() {
        return false;
    }

    @Override
    public String toString() {
        return null;
    }

    @Override
    public String getType() {
        return "<type 'void'>";
    }
}
