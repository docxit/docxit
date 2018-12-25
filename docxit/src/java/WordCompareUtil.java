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

import docxit.diff_match_patch.*;

public class WordCompareUtil {

    private static BigInteger commentId = BigInteger.valueOf(1);

    public int diff(String oldF, String newF, String resultF) throws Exception {
    	boolean diff1 = compare(new File(oldF), new File(newF), resultF);
        if(diff1) return 0;
        else return 1;
    }

    public static Boolean compare(File source,File target,String out) throws Exception{
        WordprocessingMLPackage wordMLPackage0 = WordprocessingMLPackage.load(new FileInputStream(source));
        MainDocumentPart mp0 = wordMLPackage0.getMainDocumentPart();
        ObjectFactory factory0 = Context.getWmlObjectFactory();
        List<Object> objList0 = wordMLPackage0.getMainDocumentPart().getContent();

        WordprocessingMLPackage wordMLPackage1 = WordprocessingMLPackage.load(new FileInputStream(target));
        MainDocumentPart mp1 = wordMLPackage1.getMainDocumentPart();
        ObjectFactory factory1 = Context.getWmlObjectFactory();
        List<Object> objList1 = wordMLPackage1.getMainDocumentPart().getContent();

        Comments comments = addDocumentCommentsPart(wordMLPackage0, factory0);
        if(objList0.size()!=objList1.size()){
        	System.out.println("WARNING:段落不一致");
        	System.out.println(objList0.size());
        	System.out.println(objList1.size());
            //return false;
        }
        int objSize = objList0.size();  
        if(objList0.size() > objList1.size()) objSize = objList1.size();
        for (int i = 0, len = objSize; i < len; i++) {
            if (objList0.get(i) instanceof P && !"".equals(objList0.get(i).toString().trim())) {  
                P p0 = (P) objList0.get(i);
                String s0 = p0.toString();

                P p1 = (P) objList1.get(i);
                String s1 = p1.toString();

                List<Integer> beList = rememberSpacing(s0);
                List<Integer> afList = rememberSpacing(s1);
                s0 = s0.replace(" ", "");
                s1 = s1.replace(" ", "");
                diff_match_patch dmp = new diff_match_patch(); 
                LinkedList<Diff> t = dmp.diff_main(s0,s1);
                List<Vo> diffList = new ArrayList<Vo>();
                for (Diff diff : t) {
                    Vo v = new Vo();
                    v.setKey(diff.operation.toString());
                    v.setValue(diff.text);
                    diffList.add(v);
                }

                List<Object> pContent = p0.getContent();  
                int pContentSize = pContent.size();  
                RPr fontRPr = new RPr();  
                for (int j = 0, len1 = pContentSize; j < len1; j++) {  
                    if (pContent.get(j) instanceof R) {  
                        R r = (R) pContent.get(j);  
                        fontRPr = r.getRPr();  
                    }  
                }  
                p0.getContent().clear();
                WordCompareUtil cp = new WordCompareUtil();
                cp.createComment(wordMLPackage0, mp0, factory0, p0, fontRPr, diffList,comments);
            }
        }
        //保存文档  
        writeDocxToStream(wordMLPackage0, out);
        return true;
    }


    public static List<Integer> rememberSpacing(String str){
        List<Integer> list = new ArrayList<Integer>();
        for(int i = 0;i < str.length();i++){
            if(' '==str.charAt(i)){
                list.add(i);
            }
        }
        return list;
    }

    public void createComment(WordprocessingMLPackage wordMLPackage, MainDocumentPart t, ObjectFactory factory,P p,RPr fontRPr,List<Vo> list,Comments comments)
            throws Exception {
        RPr commentRPr = getRPrStyle(factory, "微软雅黑", "41A62D", "18", STHint.EAST_ASIA, true, true, false, false, null,
                null, false, null, false, null, null, null);
        createCommentRound(factory, p, fontRPr, comments, list);
    }

    // 创建批注(选定范围)
    public void createCommentRound(ObjectFactory factory, P p, RPr fontRPr,
             Comments comments, List<Vo> list) throws Exception {
        for(int i=0;i<list.size();i++) {
            Vo v = list.get(i);
            if("EQUAL".equals(v.getKey())){
                R run = factory.createR();
                Text txt = factory.createText();
                txt.setValue(v.getValue());
                run.getContent().add(txt);
                run.setRPr(fontRPr);
                p.getContent().add(run);
            }else if("INSERT".equals(v.getKey())){
                CommentRangeStart startComment = factory.createCommentRangeStart();
                startComment.setId(commentId);
                p.getContent().add(startComment);
                R run = factory.createR();
                Text txt = factory.createText();
                txt.setValue(v.getValue());
                run.getContent().add(txt);
                run.setRPr(fontRPr);
                p.getContent().add(run);
                CommentRangeEnd endComment = factory.createCommentRangeEnd();
                endComment.setId(commentId);
                p.getContent().add(endComment);
                RPr commentRPr = getRPrStyle(factory, "微软雅黑", "41A62D", "18", STHint.EAST_ASIA, true, true, false, false, null,
                        null, false, null, false, null, null, null);
                Comment commentOne = createComment(factory, commentId, "系统管理员", new Date(), "新增："+v.getValue(), commentRPr);
                comments.getComment().add(commentOne);
                p.getContent().add(createRunCommentReference(factory, commentId));
            }else if("DELETE".equals(v.getKey()) && ((list.size()-1)==i ||"EQUAL".equals(list.get(i+1).getKey()))){
                CommentRangeStart startComment = factory.createCommentRangeStart();
                startComment.setId(commentId);
                p.getContent().add(startComment);
                R run = factory.createR();
                Text txt = factory.createText();
                txt.setValue(v.getValue());
                run.getContent().add(txt);
                run.setRPr(fontRPr);
                p.getContent().add(run);
                CommentRangeEnd endComment = factory.createCommentRangeEnd();
                endComment.setId(commentId);
                p.getContent().add(endComment);
                RPr commentRPr = getRPrStyle(factory, "微软雅黑", "FF0000", "18", STHint.EAST_ASIA, true, true, false, false, null,
                        null, false, null, false, null, null, null);
                Comment commentOne = createComment(factory, commentId, "系统管理员", new Date(), "删除："+v.getValue(), commentRPr);
                comments.getComment().add(commentOne);
                p.getContent().add(createRunCommentReference(factory, commentId));
            }else if("DELETE".equals(v.getKey()) && ((list.size()-1)==i || "INSERT".equals(list.get(i+1).getKey()))){
                CommentRangeStart startComment = factory.createCommentRangeStart();
                startComment.setId(commentId);
                p.getContent().add(startComment);
                R run = factory.createR();
                Text txt = factory.createText();
                txt.setValue(v.getValue());
                run.getContent().add(txt);
                run.setRPr(fontRPr);
                p.getContent().add(run);
                CommentRangeEnd endComment = factory.createCommentRangeEnd();
                endComment.setId(commentId);
                p.getContent().add(endComment);
                RPr commentRPr = getRPrStyle(factory, "微软雅黑", "9932CC", "18", STHint.EAST_ASIA, true, true, false, false, null,
                        null, false, null, false, null, null, null);
                Comment commentOne = createComment(factory, commentId, "系统管理员", new Date(), "替换："+list.get(i+1).getValue(), commentRPr);
                comments.getComment().add(commentOne);
                p.getContent().add(createRunCommentReference(factory, commentId));
                i++;
            }
            if(!"EQUAL".equals(v.getKey())){
                commentId = commentId.add(BigInteger.ONE);
            }
        }
    }

    public static Comments addDocumentCommentsPart(WordprocessingMLPackage wordMLPackage, ObjectFactory factory)
            throws Exception {
        CommentsPart cp = new CommentsPart();
        wordMLPackage.getMainDocumentPart().addTargetPart(cp);
        Comments comments = factory.createComments();
        cp.setJaxbElement(comments);
        return comments;
    }

    public Comments.Comment createComment(ObjectFactory factory, BigInteger commentId, String author, Date date,
            String commentContent, RPr commentRPr) throws Exception {
        Comments.Comment comment = factory.createCommentsComment();
        comment.setId(commentId);
        if (author != null) {
            comment.setAuthor(author);
        }
        if (date != null) {
            comment.setDate(toXMLCalendar(date));
        }
        P commentP = factory.createP();
        comment.getEGBlockLevelElts().add(commentP);
        R commentR = factory.createR();
        commentP.getContent().add(commentR);
        Text commentText = factory.createText();
        commentR.getContent().add(commentText);
        commentR.setRPr(commentRPr);
        commentText.setValue(commentContent);
        return comment;
    }

    public R createRunCommentReference(ObjectFactory factory, BigInteger commentId) {
        R run = factory.createR();
        R.CommentReference commentRef = factory.createRCommentReference();
        run.getContent().add(commentRef);
        commentRef.setId(commentId);
        return run;
    }

    public XMLGregorianCalendar toXMLCalendar(Date d) throws Exception {
        GregorianCalendar gc = new GregorianCalendar();
        gc.setTime(d);
        XMLGregorianCalendar xml = DatatypeFactory.newInstance().newXMLGregorianCalendar();
        xml.setYear(gc.get(Calendar.YEAR));
        xml.setMonth(gc.get(Calendar.MONTH) + 1);
        xml.setDay(gc.get(Calendar.DAY_OF_MONTH));
        xml.setHour(gc.get(Calendar.HOUR_OF_DAY));
        xml.setMinute(gc.get(Calendar.MINUTE));
        xml.setSecond(gc.get(Calendar.SECOND));
        return xml;
    }

    // 字体样式
    public static RPr getRPrStyle(ObjectFactory factory, String fontFamily, String colorVal, String fontSize, STHint sTHint,
            boolean isBlod, boolean isItalic, boolean isStrike, boolean isUnderLine,
            UnderlineEnumeration underLineStyle, String underLineColor, boolean isHightLight, String hightLightValue,
            boolean isShd, STShd shdValue, String shdColor, CTVerticalAlignRun stRunEnum) {
        RPr rPr = factory.createRPr();
        RFonts rf = new RFonts();
        if (sTHint != null) {
            rf.setHint(sTHint);
        }
        if (fontFamily != null) {
            rf.setAscii(fontFamily);
            rf.setEastAsia(fontFamily);
            rf.setHAnsi(fontFamily);
        }
        rPr.setRFonts(rf);
        if (colorVal != null) {
            Color color = new Color();
            color.setVal(colorVal);
            rPr.setColor(color);
        }
        if (fontSize != null) {
            HpsMeasure sz = new HpsMeasure();
            sz.setVal(new BigInteger(fontSize));
            rPr.setSz(sz);
            rPr.setSzCs(sz);
        }

        BooleanDefaultTrue bdt = factory.createBooleanDefaultTrue();
        if (isBlod) {
            rPr.setB(bdt);
        }
        if (isItalic) {
            rPr.setI(bdt);
        }
        if (isStrike) {
            rPr.setStrike(bdt);
        }
        if (isUnderLine) {
            U underline = new U();
            if (underLineStyle != null) {
                underline.setVal(underLineStyle);
            }
            if (underLineColor != null) {
                underline.setColor(underLineColor);
            }
            rPr.setU(underline);
        }
        if (isHightLight) {
            Highlight hight = new Highlight();
            hight.setVal(hightLightValue);
            rPr.setHighlight(hight);
        }
        if (isShd) {
            CTShd shd = new CTShd();
            if (shdColor != null) {
                shd.setColor(shdColor);
            }
            if (shdValue != null) {
                shd.setVal(shdValue);
            }
            rPr.setShd(shd);
        }
        if (stRunEnum != null) {
            rPr.setVertAlign(stRunEnum);
        }
        return rPr;
    }

    // 段落底纹
    public void setParagraphShdStyle(ObjectFactory factory, P p, boolean isShd, STShd shdValue, String shdColor) {
        if (isShd) {
            PPr ppr = factory.createPPr();
            CTShd shd = new CTShd();
            if (shdColor != null) {
                shd.setColor(shdColor);
            }
            if (shdValue != null) {
                shd.setVal(shdValue);
            }
            ppr.setShd(shd);
            p.setPPr(ppr);
        }
    }

    // 段落间距
    public void setParagraphSpacing(ObjectFactory factory, P p, boolean isSpace, String before, String after,
            boolean isLines, String beforeLines, String afterLines, boolean isLineRule, String lineValue,
            STLineSpacingRule sTLineSpacingRule) {
        PPr pPr = p.getPPr();
        if (pPr == null) {
            pPr = factory.createPPr();
        }
        Spacing spacing = new Spacing();
        if (isSpace) {
            if (before != null) {
                // 段前磅数
                spacing.setBefore(new BigInteger(before));
            }
            if (after != null) {
                // 段后磅数
                spacing.setAfter(new BigInteger(after));
            }
        }
        if (isLines) {
            if (beforeLines != null) {
                // 段前行数
                spacing.setBeforeLines(new BigInteger(beforeLines));
            }
            if (afterLines != null) {
                // 段后行数
                spacing.setAfterLines(new BigInteger(afterLines));
            }
        }
        if (isLineRule) {
            if (lineValue != null) {
                spacing.setLine(new BigInteger(lineValue));
            }
            spacing.setLineRule(sTLineSpacingRule);
        }
        pPr.setSpacing(spacing);
        p.setPPr(pPr);
    }

    // 段落对齐方式
    public void setParagraphAlign(ObjectFactory factory, P p, JcEnumeration jcEnumeration, TextAlignment textAlign) {
        PPr pPr = p.getPPr();
        if (pPr == null) {
            pPr = factory.createPPr();
        }
        if (jcEnumeration != null) {
            Jc jc = pPr.getJc();
            if (jc == null) {
                jc = new Jc();
            }
            jc.setVal(jcEnumeration);
            pPr.setJc(jc);
        }
        if (textAlign != null) {
            pPr.setTextAlignment(textAlign);
        }
        p.setPPr(pPr);
    }

    public WordprocessingMLPackage createWordprocessingMLPackage() throws Exception {
        return WordprocessingMLPackage.createPackage();
    }

    public void saveWordPackage(WordprocessingMLPackage wordPackage, File file) throws Exception {
        wordPackage.save(file);
    }

    public static void writeDocxToStream(WordprocessingMLPackage template,
            String target) throws IOException, Docx4JException {
        File f = new File(target);
        template.save(f);
    }
}