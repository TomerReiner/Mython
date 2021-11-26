package sample.types;

public class Str extends Sequence {

    private String value;

    public Str(String value) {
        this.value = value;
    }

    public Str(boolean isTemp, String value) {
        super(isTemp);
        this.value = value;
    }

    public String getValue() {
        return value;
    }

    public void setValue(String value) {
        this.value = value;
    }

    @Override
    public boolean isPrintable() {
        return true;
    }

    @Override
    public String toString() {
        return this.formatString();
    }

    @Override
    public String getType() {
        return "<type 'str'>";
    }

    public String formatString() {
        return '\'' + this.value.substring(1, this.value.length() - 1) + '\'';
    }

    public int len() {
        return this.value.length() - 2; // We need to subtract 2 from the length because there are 2 quotation marks that are not counted in the string's length.
    }
}
