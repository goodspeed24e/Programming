<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?php   
    include("mysqlcntdb.php");
	//----------���X �i�f�β��~���---------	
	$SQLStr = "SELECT transaction.*, product.* FROM transaction  AS transaction  ";
	$SQLStr .= "LEFT JOIN product AS product ON transaction.tranprodno = product.prodno WHERE (tranno='$tranno' and tranpono='$tranpono' and tranprodno='$tranprodno')";
	$res = mysql_query($SQLStr);
		
    //------- �P�_�j�M���G�O�_����------
	if (mysql_num_rows($res)>0) 
	{
	$row = mysql_fetch_array($res);
?>
<script language="JavaScript">
//-------------- �ˬd���~�ƶq--------------
function checkprodqty(fld){
   if (fld.value == ""){
      alert("���~�ƶq�ť�");
      fld.focus();
      fld.select();
   }
}
//-------------- �ˬd���~���--------------
function checkpric(fld){
   if (fld.value == ""){
      alert("���~�����쬰�ť�");
      fld.focus();
      fld.select();
   }
}
</script>
<?php $oqty=$row['tranprodqty'];  
       $opric=$row['tranpric']; 
       $ovend=$row['tranvendno']; 
?> 
<!------ �s����Ʈw,�ǵ� ininvins_mod3.php �ɮ� ------>
<form name="form1" method="post" action="ininvins_mod3.php">
  <table width="770" border="1" cellpadding="0" cellspacing="0" align="center" >
    <tr bgcolor="#FFFFFF"> 
      <td >  
        <table width="400" border="0" align="center">
          <tr> 
            <td width="100%" bgcolor="#9933FF" align="center"><font color="#FFFFFF">�i�f�ԲӸ�T</font>
            </td>
                   
          </tr>
	</table>
	<table width="770">
	  <tr>
            <td align="center"> 
              <input type="submit" name="submit" value="�ק�i�f���">
            </td>
	  </tr>
  </table>
        <table width="770" border="0" cellpadding="1" cellspacing="1" bgcolor="#99CCFF" >
          <tr>           
            <td width="241" align="center"><font >�i�f�渹</font></td>
            <td width="522" align="left"><?=$row['tranno']?> 
			  <input  type="hidden" name="tranno" size="10" value="<?=$row['tranno']?>">
		      <input  type="hidden" name="oqty" size="10" value="<?=$oqty;?>">
			  <input  type="hidden" name="opric" size="10" value="<?=$opric;?>">
			  <input  type="hidden" name="ovend" size="10" value="<?=$ovend;?>">			 
            </td>
            
          </tr>
          <tr> 
            <td width="241" align="center"><font >���~�s��</font></td>
            <td width="522" align="left"><?=$row['tranprodno']?>
			    <input type="hidden" name="tranprodno" size="10" value="<?=$row['tranprodno']?>">
            </td>
          </tr>
		  <tr> 
            <td width="241" align="center"><font >���~�W��</font></td>
            <td width="522" align="left"><?=$row['prodname']?> 
			    <input type="hidden" name="tranprodname" size="40" value="<?=$row['prodname']?>">			   
            </td>
          </tr>
          <tr>
            <td width="241" align="center"><font >���ʳ渹</font> </td>
            <td width="522" align="left"><?=$row['tranpono']?>
                <input type="hidden" name="tranpono" size="10" value="<?=$row['tranpono']?>">
            </td>            
          </tr>
		   <tr>            
            <td width="241" height="22" align="center">�t�ӽs��</td>
            <td width="522" height="22" align="left"><?=$row['tranvendno']?>
                <input type="hidden" name="tranvendno" size="10" value="<?=$row['tranvendno']?>">
            </td>			           
          </tr>
          <tr>
            <td width="241" height="22" align="center"><font >�i�f���</font> </td>
            <td width="522" height="22" align="left">
                <input type="text" name="trandate" size="10" value="<?=$row['trandate']?>">
            </td>            
          </tr>         
		  <tr>
			<td width="241" height="22" align="center">���~�ƶq</td>
            <td width="522" height="22">
			    <!------------------ �ק���ˬd���~�ƶq--------------> 
                <input type="text" name="tranprodqty" size="6" value="<?=$row['tranprodqty']?>"  onblur="checkprodqty(this)">
            </td>           
          </tr>
		  <tr>
			<td width="241" height="22" align="center">���~���</td>
            <td width="522" height="22"> 
                <input type="text" name="tranunit" size="10" value="<?=$row['tranunit']?>">
            </td>           
          </tr>
		  <tr> 
            <td width="241" align="center">���~���</td>
            <td width="522">
			    <!---------------- �ק���ˬd���~���-------------->
                <input type="text" name="tranpric" size="10" value="<?=$row['tranpric']?>"   onBlur="checkpric(this)" >
            </td>
		  </tr>		   
		</td>
    </tr> 
  </table>
</form>
<?
}
else
	{
	 $msg="�L���i�f��";
	 include("windowsclose.php");
	}
?>
</body>
</html>
