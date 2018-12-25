package docxit;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.LinkedList;
import java.util.List;

import javax.xml.bind.JAXBException;
import javax.xml.datatype.DatatypeFactory;
import javax.xml.datatype.XMLGregorianCalendar;

import org.docx4j.jaxb.Context;
import org.docx4j.openpackaging.exceptions.Docx4JException;
import org.docx4j.openpackaging.packages.WordprocessingMLPackage;
import org.docx4j.openpackaging.parts.WordprocessingML.CommentsPart;
import org.docx4j.openpackaging.parts.WordprocessingML.MainDocumentPart;
import org.docx4j.wml.BooleanDefaultTrue;
import org.docx4j.wml.CTShd;
import org.docx4j.wml.CTVerticalAlignRun;
import org.docx4j.wml.Color;
import org.docx4j.wml.CommentRangeEnd;
import org.docx4j.wml.CommentRangeStart;
import org.docx4j.wml.Comments;
import org.docx4j.wml.Highlight;
import org.docx4j.wml.HpsMeasure;
import org.docx4j.wml.Jc;
import org.docx4j.wml.JcEnumeration;
import org.docx4j.wml.ObjectFactory;
import org.docx4j.wml.P;
import org.docx4j.wml.PPr;
import org.docx4j.wml.PPrBase.Spacing;
import org.docx4j.wml.PPrBase.TextAlignment;
import org.docx4j.wml.R;
import org.docx4j.wml.RFonts;
import org.docx4j.wml.RPr;
import org.docx4j.wml.STHint;
import org.docx4j.wml.STLineSpacingRule;
import org.docx4j.wml.STShd;
import org.docx4j.wml.Text;
import org.docx4j.wml.U;
import org.docx4j.wml.UnderlineEnumeration;
import org.docx4j.wml.Comments.Comment;
import org.docx4j.wml.Body;
import org.docx4j.wml.Document;

public class WordMergeUtil {
	
	public void merge(String branch0, String branch1, String path0, String path1, String outpath) throws FileNotFoundException, Docx4JException, JAXBException {
		WordprocessingMLPackage wordMLPackage0 = WordprocessingMLPackage.load(new FileInputStream(new File(path0)));
        List<Object> objList0 = wordMLPackage0.getMainDocumentPart().getContent();
        
        WordprocessingMLPackage wordMLPackage1 = WordprocessingMLPackage.load(new FileInputStream(new File(path1)));
        List<Object> objList1 = wordMLPackage1.getMainDocumentPart().getContent();
        
        WordprocessingMLPackage wordMLPackage2 = WordprocessingMLPackage.createPackage();
        MainDocumentPart mp2 = wordMLPackage2.getMainDocumentPart();
        ObjectFactory factory2 = Context.getWmlObjectFactory();
        Document doc = mp2.getContents();
		Body body = doc.getBody();
        
        int index0 = 0;
        int index1 = 0;
        int i = 0, len0 = 0;
        int j = 0, len1 = 0;
        boolean isconflict = false;
        
        
        for (i = index0, len0 = objList0.size(); i < len0; i++) {
        	if (!(objList0.get(i) instanceof P && !"".equals(objList0.get(i).toString().trim()))) {
        		continue;
        	}
        	P p0 = (P) objList0.get(i);
            String s0 = p0.toString();
        	for (j = index1, len1 = objList1.size(); j < len1; j++) {
        		P p1 = (P) objList1.get(j);
                String s1 = p1.toString();
                if(s0.equals(s1)) {
                	if((i - index0) != 0) {
                		boolean isEmpty = true;
                		for(int k = index0; k < j; k++) {
                			if(objList0.get(k) instanceof P && !"".equals(objList0.get(k).toString().trim()))
                				isEmpty = false;
                		}
                		if(!isEmpty) {
                			isconflict = true;
                			addbranchsymbol(body, factory2, branch0);
                			while((i - index0) != 0) {
                				mp2.addObject(objList0.get(index0));
                				index0++;
                			}
                			addsplitline(body, factory2);
                		} else index0 = i;
                	}
                	if((j - index1) != 0) {
                		boolean isEmpty = true;
                		for(int k = index1; k < j; k++) {
                			if(objList1.get(k) instanceof P && !"".equals(objList1.get(k).toString().trim()))
                				isEmpty = false;
                		}
                		if(!isEmpty) isconflict = true;
                		if(!isEmpty) addsplitline(body, factory2);
                		while((j - index1) != 0) {
                    		mp2.addObject(objList1.get(index1));
                    		index1++;
                    	}
                		if(!isEmpty) addbranchsymbol(body, factory2, branch1);
                	}
                	
                	mp2.addObject(objList1.get(index1));
                	index0++;
                	index1++;
                	break;
                }
        	}
        }
        if((len0 - index0) > 0) {
    		isconflict = true;
    		addbranchsymbol(body, factory2, branch0);
    		while((len0 - index0) != 0) {
        		mp2.addObject(objList0.get(index0));
        		index0++;
        	}
    		addsplitline(body, factory2);
    	}
    	if((len1 - index1) > 0) {
    		addsplitline(body, factory2);
    		while((len1 - index1) != 0) {
        		mp2.addObject(objList1.get(index1));
        		index1++;
        	}
    		addbranchsymbol(body, factory2, branch1);
    	}
    	wordMLPackage2.save(new File(outpath));
    	if(isconflict) System.out.println("ERROR: 请解决冲突    Filepath:" + outpath);
	}

	public void addsplitline(Body body, ObjectFactory factory) {
		Color red = new Color();
        red.setVal("FF0000");
        RPr rprR = factory.createRPr();
        rprR.setColor(red);
		
		P para = factory.createP();
		R run = factory.createR();
		Text text = factory.createText();
		run.setRPr(rprR);
		text.setValue("--------------------");
		run.getContent().add(text);
		para.getContent().add(run);
		body.getContent().add(para);
	}
	
	public void addbranchsymbol(Body body, ObjectFactory factory, String branch) {
		Color red = new Color();
        red.setVal("FF0000");
        Color blue = new Color();
        blue.setVal("0000FF");
        RPr rprR = factory.createRPr();
        rprR.setColor(red);
        RPr rprB = factory.createRPr();
        rprB.setColor(blue);
        
        P para = factory.createP();
		R run0 = factory.createR();
		Text text0 = factory.createText();
		text0.setValue("-------");
		run0.getContent().add(text0);
		run0.setRPr(rprR);
		para.getContent().add(run0);
		
		R run1 = factory.createR();
		Text text1 = factory.createText();
		text1.setValue(branch);
		run1.getContent().add(text1);
		run1.setRPr(rprB);
		para.getContent().add(run1);
		
		R run2 = factory.createR();
		Text text2 = factory.createText();
		text2.setValue("------");
		run2.getContent().add(text2);
		run2.setRPr(rprR);
		para.getContent().add(run2);
		
		body.getContent().add(para);
	}
	
}