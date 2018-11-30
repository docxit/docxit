package docxit;

public interface FileOperation {
	public int diff(String oldFilePath, String newFilePath);
	public int merge(String oldFilePath, String newFilePath, String resultFilePath,
			String Branchname0, String Branchname1);
}
