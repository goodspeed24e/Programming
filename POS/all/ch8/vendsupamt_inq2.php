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

//----------------------- ���X vetys ����-----------------------------------------------
	$SQLStr2 = "SELECT * FROM vety";
	$res2 = mysql_query($SQLStr2);
//------------------------ �P�_�j�M���G�O�_����--------------------------------------------	
	if (mysql_num_rows($res)>0) 
	{
	$row = mysql_fetch_array($res);
?>
<!---���槹��,�^����----->
<form name="form1" method="post" action="../index.php?Select=10">
  <table width="770" border="1" cellpadding="0" cellspacing="0" align="center" >
    <tr> 
      <td  bgcolor="#FFFFFF">  
        <table width="400" border="0" align="center">
          <tr> 
            <td width="100%" bgcolor="#9933FF" align="center"><font color="#FFFFFF">���I�b�ڳ]�w</font>
            </td>          
          </tr>
	</table>
	<table width="770">
	  <tr>
            <td align="center"> 
              <input type="submit" name="submit" value="�j�M���I�b�ڳ]�w">
            </td>
	  </tr>
  </table>
<!--//------------�j�M��Ƥ��e�e�{,�t�����I�b�ڸ�Ʃ���-------------------------------------------->	  
        <table width="770" border="0" cellpadding="1" cellspacing="1" bgcolor="#99CCFF" >
		   <tr>           
            <td width="201" align="center">�t�ӧǸ�</td>
            <td align="left" colspan="3"><?=$row[vendno]?>	
				 <input  type="hidden" name="vendpricper" size="3" value="<?=$row['vendno']?>">        
            </td>
		 </tr>	
          <tr>           
            <td width="201" align="center">�t�����O</td>
            <td width="204" align="left"><?=$row['vendtype']?>		        
            </td>
            <td width="100" align="center">�t��²��</td>
            <td width="252" align="left"><?=$row['vendsname']?>             
            </td>
          </tr>
          <tr> 
            <td width="201" align="center">�t�ӦW��</td>
            <td width="204" align="left"><?=$row['vendname']?>               
            </td>
            <td width="100" align="center">�t�d�H</td>
            <td width="252" align="left"><?=$row['vendleader']?>             
          </tr>
          <tr>
            <td width="201" align="center">�Τ@�s��</td>
            <td width="204" align="left"><?=$row['vendinvoice']?>               
            </td>
            <td width="100" align="center">�p���H</td>
            <td width="252" align="left"><?=$row['vendcontact']?>               
            </td>
          </tr>
		  
		 <tr>
			<td width="201" height="22" align="center">���q�a�}</td>
            <td width="204" height="22"><?=$row['vendadr']?>                
            </td>           
          </tr>
		  <tr>
			<td width="201" height="22" align="center">���I���B</td>
            <td width="204" height="22"> 
			   <input type="text" name="vendapamt" size="8"  value="<?=$row[vendapamt]?>">
            </td>           
          </tr>
		  <tr>
			<td width="201" height="22" align="center">�w�I���B</td>
            <td width="204" height="22">
			 <input type="text" name="vendprepamt" size="8" value="<?=$row[vendprepamt]?>">
			</td>           
          </tr>
		  <tr> 
            <td width="201" align="center">���I�b�|�p���</td>
            <td width="204"> 
                <input type="text" name="vendapdc" size="10" value="<?=$row['vendapdc']?>">
            </td>
		  </tr>
		  <tr> 
            <td width="201" align="center">�w�I�ڷ|�p���</td>
            <td width="204"> 
                <input type="text" name="vendprepdc" size="10" value="<?=$row['vendprepdc']?>">
            </td>
		  </tr>
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
