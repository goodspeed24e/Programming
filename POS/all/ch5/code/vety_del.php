<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=big5">
<title>�R���t�����O</title>
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
if ($check == del) 
	{
		//---------- �q��Ʈw���t�����O�R��----------
		$SQLStr = "DELETE FROM vety WHERE vetyno = '$vetyno' LIMIT 1 ";
		mysql_query("SET NAMES 'big5'");
        mysql_query("SET CHARACTER SET big5"); 
		mysql_query($SQLStr);
		//---------- �q��Ʈw���t�����O�R��---------- 
	}

	// ----------���X�Ҧ��t�����O ----------
	$SQLStr = "SELECT * FROM vety";	
	$res = mysql_query($SQLStr);
	// ----------���X�Ҧ��t�����O----------	
?>
<form name="form1" method="post" action="./code/vety_del_db.php">
  <table width="750" border="1" cellpadding="0" cellspacing="0" align="center" bordercolor="#0000FF">
    <tr> 
      <td  bgcolor="#CCFFFF"> 
        <table width="400" border="0" align="center">
          <tr> 
            <td width="100%" bgcolor="#CCFFFF" align="center"> 
             <font bgcolor="#CCFFFF">�R���t�����O</font>
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
	       //---------- ���X�{���t�����O�çe�{������W---------- 
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
		  //---------- ���X�{���t�����O�W�٨çe�{������W---------- 
          ?>    
	   </table>
      </td>
    </tr>
 </table>
 <table width="400" border="0" align="center">          
          <tr > 
            <td bgcolor="#0000CC" align="center" ><font color="#FFFFFF">���O</font>  
                <input type="text" name="vetyno">
				<input type="text" name="vetyname">
                <input type="submit" name="Submit" value="�R��">
            </td>			
          </tr> 
	 </table>        
</table>
</form>

