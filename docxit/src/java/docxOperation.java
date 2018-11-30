package docxit;

import java.io.FileNotFoundException;

import javax.xml.bind.JAXBException;

import org.docx4j.openpackaging.exceptions.Docx4JException;

import docxit.WordMergeUtil;

public class docxOperation implements FileOperation{

	public int diff(String oldFilePath, String newFilePath) {
		String resultFilePath = "diff_" + oldFilePath;
		WordCompareUtil cp = new WordCompareUtil();
		try {
			cp.diff(oldFilePath, newFilePath, resultFilePath);
		} catch (Exception e) {
			e.printStackTrace();
			return 1;
		}
		return 0;
	}

	public int merge(String oldFilePath, String newFilePath, String resultFilePath, String Branchname0, String Branchname1) {
		WordMergeUtil M = new WordMergeUtil();
		try {
			M.merge(Branchname0, Branchname1, oldFilePath, newFilePath, resultFilePath);
		} catch (FileNotFoundException e) {
			e.printStackTrace();
			return 1;
		} catch (Docx4JException e) {
			e.printStackTrace();
			return 2;
		} catch (JAXBException e) {
			e.printStackTrace();
			return 3;
		}
		return 0;
	}
	
}
