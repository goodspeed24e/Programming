<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=big5">
<title>�ק�Ȥ����O</title>
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
// -----���X�Ȥ����O----------- 	
$SQLStr = "SELECT * FROM cuty";	
$res = mysql_query($SQLStr);
// -----���X�Ȥ����O-----------	
?>
<form name="form1" method="post" action="./code/cuty_mod_db.php">
  <table width="750" border="1" cellpadding="0" cellspacing="0" align="center" bordercolor="#0000FF">
    <tr> 
      <td bgcolor="#CCFFFF"> 
        <table width="400" border="0" align="center">
          <tr> 
            <td width="100%"  bgcolor="#CCFFFF" align="center"> 
             <font  color="#000000">�ק�Ȥ����O</font>
            </td>           
          </tr>
        </table>
  <table width="750" border="1" cellspacing="0" cellpadding="0" bordercolor="#9999FF">
    <tr>
      <td>
        <table width="750" border="1" cellspacing="0" bgcolor="#FFFFFF">
          <tr> 
            <td bgcolor="#CCCCCC" align="center">�{���Ȥ����O�N�X</td>
			<td bgcolor="#CCCCCC" align="center">�{���Ȥ����O�W��</td>
          </tr>
          <?
	       //---------- ���X�{���Ȥ����O�çe�{������W----------
	       $sql="select * from cuty ";
           $rows=mysql_query($sql);
           while(list($cutyno , $cutyname )=@mysql_fetch_row($rows)) {
           echo "
                 <tr bgcolor='#F7F7F7'>
                 <td><font size='-1'>$cutyno</font></td>
                 <td><font size='-1'>$cutyname</font></td>                
                 </tr>
                 ";
            }
	        //---------- ���X�{���Ȥ����O�çe�{������W----------
           ?>    
	   </table>
      </td>
    </tr>
 </table>
 <table width="400" border="0" align="center">          
          <tr > 
            <td   bgcolor="#0000CC" align="center" ><font color="#FFFFFF">���O</font> 
                <input type="text" name="cutyno">
				<input type="text" name="cutyname">
                <input type="submit" name="Submit" value="�ק�">
            </td>
			
          </tr> 
	 </table>        
</table>
</form>

