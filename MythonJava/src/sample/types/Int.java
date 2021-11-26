package sample.types;

public class Int extends Type {

    private int value;

    public Int(int value) {
        this.value = value;
    }

    public Int(boolean isTemp, int value) {
        super(isTemp);
        this.value = value;
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }

    @Override
    public boolean isPrintable() {
        return true;
    }

    @Override
    public String toString() {
        return "" + this.value;
    }

    @Override
    public String getType() {
        return "<type 'int'>";
    }
}
