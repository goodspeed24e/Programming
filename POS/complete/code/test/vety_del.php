<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=big5">
<title>�i�P�sweb based�t��</title>
<style type="text/css">
<!--
.style1 {color: #FF0000}
-->
</style>
</head>
<?php
	include("swmcntdb.php");
// �s������-- �Y--  counterhead.php + counterbody.php �Y���s�����Ƥp�{�� 
// include("swmcnthead.php");   
		
//²���d����-- �Y-- boardead.php + boardbody.php �Y��²���d����
//    include("swmbdhead.php");
?>
<?php
if ($check == del) 
	{
		// �N���O�s�W�ܸ�Ʈw�� BEGIN
		$SQLStr = "DELETE FROM vety WHERE vetyno = '$vetyno' LIMIT 1 ";
		mysql_query("SET NAMES 'big5'");
        mysql_query("SET CHARACTER SET big5"); 
		mysql_query($SQLStr);
		// �N���O�s�W�ܸ�Ʈw�� END
	}

	// ���X�Ҧ����O BEGIN	
	$SQLStr = "SELECT * FROM vety";	
	$res = mysql_query($SQLStr);
	// ���X�Ҧ����O END		
	
?>

<form name="form1" method="post" action="iwmfile_vety_del_db.php">
  <table width="750" border="1" cellpadding="0" cellspacing="0" align="center" bordercolor="#0000FF">
    <tr> 
      <td bgcolor="#FFFFCC"> 
        <table width="400" border="0" align="center">
          <tr> 
            <td width="60%" bgcolor="#9933FF" align="center"> 
             <font color="#FFFFFF">�R���t�����O</font>
            </td>
            <td width="25%" bgcolor="#9966FF">&nbsp;</td>
            <td width="10%" bgcolor="#9999FF">&nbsp;</td>
            <td width="3%" bgcolor="#9999FF">&nbsp;</td>
            <td width="2%" bgcolor="#99CCFF">&nbsp;</td>
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
	// ���X�Ҧ��Ȥ����O�W�٨çe�{������W BEGIN
	//$num =@mysql_num_rows($res);
	//for ($i=0;$i<$num;$i++)
	//{
	//$row = mysql_fetch_array($res);
	//echo "<tr><td align='center'>" . $row['cutyname'] . "</td></tr>";
	//}
	// ���X�Ҧ��Ȥ����O�W�٨çe�{������W END
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
?>    
	   </table>
      </td>
    </tr>
 </table>
 <table width="400" border="0" align="center">          
          <tr > 
            <td bgcolor="#99CCFF" align="center" >���O 
                <input type="text" name="vetyno">
				<input type="text" name="vetyname">
                <input type="submit" name="Submit" value="�R��">
            </td>
			
          </tr> 
	 </table>        
</table>
</form>

