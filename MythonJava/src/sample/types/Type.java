package sample.types;

public abstract class Type {

    protected boolean isTemp;

    public Type() {
        this(false);
    }

    public Type(boolean isTemp) {
        this.isTemp = isTemp;
    }

    public void setTemp(boolean temp) {
        this.isTemp = temp;
    }

    public abstract boolean isPrintable();

    public abstract String toString();

    public abstract String getType();

}
