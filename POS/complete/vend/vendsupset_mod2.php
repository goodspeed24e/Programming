<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?
    include("mysqlcntdb.php");	
//-----------------------��Ƭ������X, �N vend, vety ���X�_��------------------------------		
	$SQLStr = "SELECT vend.*, vety.*  FROM vend AS vend ";
	$SQLStr .= "LEFT JOIN vety AS vety ON vend.vendtype = vety.vetyno WHERE vendno='$vendno'";	
	$res = mysql_query($SQLStr);	
	
//----------------------- ���X satys ����-----------------------------------------------
	$SQLStr2 = "SELECT * FROM saty";
	$res2 = mysql_query($SQLStr2);	

	if (mysql_num_rows($res)>0) 
	{
	$row = mysql_fetch_array($res);
?>
<!---�]�w�j�M����,�ǤJvendsupset_mod3.php---------------------->	
<form name="form1" method="post" action="vendsupset_mod3.php?vendno='.$vendno.'">
  <table width="770" border="1" cellpadding="0" cellspacing="0" align="center" >
    <tr> 
      <td  bgcolor="#FFFFFF">  
        <table width="770" border="0" align="center">
          <tr> 
            <td width="60%" bgcolor="#9933FF" align="center"><font color="#FFFFFF">�t�Ӷi�f�]�w</font>
            </td>
            <td align="center"> 
              <input type="submit" name="submit" value="�ק�t�Ӷi�f�]�w">
            </td>
	  </tr>
  </table>
        <table width="770" border="0" cellpadding="1" cellspacing="1" bgcolor="#99CCFF" >
		   <tr>           
            <td width="86" align="center">�t�ӧǸ�</td>
            <td width="209" align="left" colspan="3"><?=$row[vendno]?>	
				 <input  type="hidden" name="vendpricper" size="3" value="<?=$row['vendno']?>">        
            </td>
		 </tr>	
          <tr>           
            <td width="86" align="center">�t�����O</td>
            <td width="209" align="left"><?=$row['vendtype']?>		        
            </td>
            <td width="85" align="center">�t��²��</td>
            <td width="201" align="left"><?=$row['vendsname']?>             
            </td>
          </tr>
          <tr> 
            <td width="86" align="center">�t�ӦW��</td>
            <td width="209" align="left"><?=$row['vendname']?>               
            </td>
            <td width="96" align="center">�t�d�H</td>
            <td width="201" align="left"><?=$row['vendleader']?>             
          </tr>
          <tr>
            <td width="86" align="center">�Τ@�s��</td>
            <td width="209" align="left"><?=$row['vendinvoice']?>               
            </td>
            <td width="96" align="center">�p���H</td>
            <td width="201" align="left"><?=$row['vendcontact']?>               
            </td>
          </tr>
		  
		 <tr>
			<td width="86" height="22" align="center">���q�a�}</td>
            <td width="187" height="22"><?=$row['vendadr']?>                
            </td>           
          </tr>
		  <tr>
			<td width="100" height="22" align="center">���b��</td>
            <td width="187" height="22"> 
			   <input type="text" name="vendclosdate" size="10" maxlength="8" value="<?=substr($row['vendclosdate'],0,10)?>">
            </td>           
          </tr>
		  <tr>
			<td width="86" height="22" align="center">�i�f���O</td>
            <td width="187" height="22"> 
<?
 		$num = mysql_num_rows($res2);

//--------------------------------�e�{�t�����O���W��,�ѿ��---------------------------------------------
                echo "<select name='vendprictype'>";
		echo "<option value='" . $row['vetyno'] . "'>" . $row['vetyname'] . "</option>";
		for ($i=0;$i<$num;$i++)
		{
		  $row2 = mysql_fetch_array($res2);
	          echo "<option value='" . $row2['satyno'] . "'>" . $row2['satyname'] . "</option>";
		}
                echo "</select>";		
?>
<?=$row2['vendprictype']?>
</td>           
          </tr>
		  <tr> 
            <td width="86" align="center">�ꦬ���</td>
            <td width="187"> 
                <input type="text" name="vendpricper" size="3" value="<?=$row[vendpricper]?>">
            </td>
		  </tr>
		    
		<!--</td>
    </tr> -->
  </table>
</form>
<?
}
else
	{
	 $msg="�L���t��";
	 include("windowsclose.php");		
	}
?>
</body>
</html>
