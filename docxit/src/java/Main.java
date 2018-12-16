package docxit;
import java.lang.reflect.*;

public class Main {

	public static void main(String[] args) {
		String[] suffix = args[1].split("\\.",2);
		String className;
		if(suffix.length <= 1) className = "";
		else className = suffix[1] + "Operation";
		Class<?> op = null;
		try {
			op = Class.forName("docxit."+className);
		} catch (ClassNotFoundException e) {
			try {
				op = Class.forName("docxit."+"defaultOperation");
			} catch (ClassNotFoundException e1) {
				e1.printStackTrace();
			}
		}
		Method method = null;
		try {
			if(args[0].equals("diff")) {
				method = op.getMethod(args[0], String.class, String.class);
				method.invoke(op.newInstance(), args[1], args[2]);
			}
			else if (args[0].equals("merge")) {
				method = op.getMethod(args[0], String.class, String.class, String.class, String.class, String.class);
				method.invoke(op.newInstance(), args[1], args[2], args[3], args[4], args[5]);
			} else {
				System.out.println("None method found!");
			}
		} catch (NoSuchMethodException e1) {
			e1.printStackTrace();
		} catch (SecurityException e1) {
			e1.printStackTrace();
		} catch (IllegalAccessException e) {
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			e.printStackTrace();
		} catch (InvocationTargetException e) {
			e.printStackTrace();
		} catch (InstantiationException e) {
			e.printStackTrace();
		}
	}
}
