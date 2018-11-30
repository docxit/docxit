package docxit;
import java.lang.reflect.*;

public class Main {

	public static int main(String[] args) {
		String[] suffix = args[1].split(".",2);
		String className = suffix[1] + "Operation";
		Class<?> op = null;
		try {
			op = Class.forName("docxit."+className);
		} catch (ClassNotFoundException e) {
			try {
				op = Class.forName("docxit."+"defaultOperation");
			} catch (ClassNotFoundException e1) {
				return 1;
			}
		}
		Method method = null;
		try {
			method = op.getMethod(args[0]);
		} catch (NoSuchMethodException e1) {
			return 1;
		} catch (SecurityException e1) {
			return 1;
		}
		try {
			method.invoke(op.newInstance());
		} catch (IllegalAccessException e) {
			return 1;
		} catch (IllegalArgumentException e) {
			return 1;
		} catch (InvocationTargetException e) {
			return 1;
		} catch (InstantiationException e) {
			return 1;
		}
		return 0;
	}
}
