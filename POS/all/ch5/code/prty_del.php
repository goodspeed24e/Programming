<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=big5">
<title>�R�����~���O</title>
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
		//---------- �q��Ʈw�����O�R��----------
		$SQLStr = "DELETE FROM prty WHERE prtyno = '$prtyno' LIMIT 1 ";
		mysql_query("SET NAMES 'big5'");
        mysql_query("SET CHARACTER SET big5"); 
		mysql_query($SQLStr);
		//---------- �q��Ʈw�����O�R��---------- 
	}

	// ----------���X�Ҧ����O ----------
	$SQLStr = "SELECT * FROM prty";	
	$res = mysql_query($SQLStr);
	// ----------���X�Ҧ����O----------	
?>
<form name="form1" method="post" action="./code/prty_del_db.php">
  <table width="750" border="1" cellpadding="0" cellspacing="0" align="center" bordercolor="#0000FF">
    <tr> 
      <td  bgcolor="#CCFFFF"> 
        <table width="400" border="0" align="center">
          <tr> 
            <td width="100%" bgcolor="#CCFFFF" align="center"> 
             <font bgcolor="#CCFFFF">�R�����~���O</font>
            </td>            
          </tr>
        </table>
  <table width="750" border="1" cellspacing="0" cellpadding="0" bordercolor="#9999FF">
    <tr>
      <td>
        <table width="750" border="1" cellspacing="0" bgcolor="#FFFFFF">
          <tr> 
            <td bgcolor="#CCCCCC" align="center">�{�����~���O�N�X</td>
			<td bgcolor="#CCCCCC" align="center">�{�����~���O�W��</td>
          </tr>
          <?
	       //---------- ���X�{�����~���O�çe�{������W---------- 
	       $sql="select * from prty ";
           $rows=mysql_query($sql);
           while(list($prtyno , $prtyname )=@mysql_fetch_row($rows)) {
               echo "
                    <tr bgcolor='#F7F7F7'>
                       <td><font size='-1'>$prtyno</font></td>
                       <td><font size='-1'>$prtyname</font></td>                
                    </tr>
                    ";
                     }
		  //---------- ���X�{�����~���O�W�٨çe�{������W---------- 
          ?>    
	   </table>
      </td>
    </tr>
 </table>
 <table width="400" border="0" align="center">          
          <tr > 
            <td bgcolor="#0000CC" align="center" ><font color="#FFFFFF">���O</font>  
                <input type="text" name="prtyno">
				<input type="text" name="prtyname">
                <input type="submit" name="Submit" value="�R��">
            </td>			
          </tr> 
	 </table>        
</table>
</form>

