<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=big5">
<title>�קﲣ�~���</title>
<style type="text/css">
<!--
.style1 {color: #FF0000}
-->
</style>
</head>
<?php
//----------�s����Ʈw----------
include("mysqlcntdb.php");
//----------�s����Ʈw----------
// -----���X���~���----------- 	
$SQLStr = "SELECT * FROM prun";	
$res = mysql_query($SQLStr);
// -----���X���~���-----------	
?>
<form name="form1" method="post" action="./code/prun_mod_db.php">
  <table width="750" border="1" cellpadding="0" cellspacing="0" align="center" bordercolor="#0000FF">
    <tr> 
      <td bgcolor="#CCFFFF"> 
        <table width="400" border="0" align="center">
          <tr> 
            <td width="100%"  bgcolor="#CCFFFF" align="center"> 
             <font  color="#000000">�קﲣ�~���</font>
            </td>           
          </tr>
        </table>
  <table width="750" border="1" cellspacing="0" cellpadding="0" bordercolor="#9999FF">
    <tr>
      <td>
        <table width="750" border="1" cellspacing="0" bgcolor="#FFFFFF">
          <tr> 
            <td bgcolor="#CCCCCC" align="center">�{�����~���N�X</td>
			<td bgcolor="#CCCCCC" align="center">�{�����~���W��</td>
          </tr>
          <?
	       //---------- ���X�{�����~���çe�{������W----------
	       $sql="select * from prun ";
           $rows=mysql_query($sql);
           while(list($prunno , $prunname )=@mysql_fetch_row($rows)) {
           echo "
                 <tr bgcolor='#F7F7F7'>
                 <td><font size='-1'>$prunno</font></td>
                 <td><font size='-1'>$prunname</font></td>                
                 </tr>
                 ";
            }
	        //---------- ���X�{�����~���çe�{������W----------
           ?>    
	   </table>
      </td>
    </tr>
 </table>
 <table width="400" border="0" align="center">          
          <tr > 
            <td   bgcolor="#0000CC" align="center" ><font color="#FFFFFF">���</font> 
                <input type="text" name="prunno">
				<input type="text" name="prunname">
                <input type="submit" name="Submit" value="�ק�">
            </td>
			
          </tr> 
	 </table>        
</table>
</form>

