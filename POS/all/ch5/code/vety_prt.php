<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=big5">
<title>���~���O�C��</title>
<style type="text/css">
<!--
.style1 {color: #FF0000}
-->
</style>
</head>
<!!-----------�C�L�]�w----------!>
<body>
<!!----------�C�L�]�w-----------!>
<?php
//----------�s����Ʈw----------
	include("mysqlcntdb.php");
//----------�s����Ʈw----------

//---------- ���X�Ҧ��t�����O----------	
$SQLStr = "SELECT * FROM vety";	
$res = mysql_query($SQLStr);
//---------- ���X�Ҧ��t�����O----------		
	
?>

<form name="form1" method="post" action="./code/vety_prt_db.php">
  <table width="750" border="1" cellpadding="0" cellspacing="0" align="center" bordercolor="#0000FF">
    <tr> 
      <td bgcolor="#CCFFFF"> 
        <table width="400" border="0" align="center">
          <tr> 
            <td width="100%"  bgcolor="#CCFFFF" align="center"> 
             <font  color="#000000">�C�L�t�����O</font>
            </td>           
          </tr>
        </table>
  <table width="750" border="1" cellspacing="0" cellpadding="0" bordercolor="#9999FF">
    <tr>
      <td>
        <table width="750" border="1" cellspacing="0" bgcolor="#FFFFFF">
          <tr> 
            <td bgcolor="#CCCCCC" align="center">�{���t�����O�N�X</td>
			<td bgcolor="#CCCCCC" align="center">�{���t�����O�W��</td>
          </tr>
          <?
	       //---------- ���X�Ҧ��t�����O�W�٨çe�{������W---------- 
	       $sql="select * from vety ";
           $rows=mysql_query($sql);
           while(list($vetyno , $vetyname )=@mysql_fetch_row($rows)) {
           echo "
                 <tr bgcolor='#F7F7F7'>
                 <td><font size='-1'>$vetyno</font></td>
                 <td><font size='-1'>$vetyname</font></td>                
                </tr>
               ";
           }
	       //---------- ���X�Ҧ��t�����O�W�٨çe�{������W---------- 
         ?>    
	   </table>
      </td>
    </tr>
 </table>
 <table width="400" border="0" align="center">          
          <tr > 
            <td bgcolor="#0000CC" align="center" > 			                
                <input type="submit" name="Submit" value="�C�L">
            </td>
			
          </tr> 
	 </table>        
</table>

</form>
</body>

