<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?php   
    include("mysqlcntdb.php");
// -------------���X��ܤ����~�����---------------
	$SQLStr = "SELECT *  FROM product  WHERE prodno='$prodno'";	
	$res = mysql_query($SQLStr);
// -------------���X���~���O�����---------------
	$SQLStr2 = "SELECT * FROM prty";
	$res2 = mysql_query($SQLStr2);	

	if (mysql_num_rows($res)>0) 
	{
	$row = mysql_fetch_array($res);
?>
<!----����קﭶ���e�{,�ǤJ�j�M����invqty_mod3.php------------------------->
<form name="form1" method="post" action="invqty_mod3.php">
<table width="780" border="1" cellpadding="0" cellspacing="0" align="center" >
    <tr> 
	<table  border="1" align="center" bgcolor="#99CCFF" cellpadding="0" cellspacing="0" width="780">
          <tr  bgcolor="#99CCFF"> 
            <td  bgcolor="#9933FF" align="center"> 
             <font color="#FFFFFF">�קﲣ�~�w�s���</font>
            </td> 
			  <td align="center"> 
              <input type="submit" name="submit" value="�קﲣ�~�w�s���">
            </td>                 
          </tr>
        </table>
        <table width="780" border="1" cellpadding="0" cellspacing="0" bgcolor="#99CCFF"    align="center">
          <tr> 
            <td width="103" align="center">���~�s��</td>
            <td width="187"><?=$row['prodno']?> 
                <input  type="hidden" name="prodno" size="10" value="<?=$row['prodno']?>">
            </td>
            <td width="96" align="center">���~�W��</td>
            <td width="351"><?=$row['prodname']?>
            </td>
          </tr>
          <tr> 
            <td width="103" align="center">�W�满��</td>
            <td width="187"><?=$row['prodsdesp']?>                
            </td>
            <td width="96" align="center">���~���O</td>
            <td width="351"><?=$row['prodtype']?>              
            </td>
          </tr>
          <tr> 
            <td width="103" align="center">�����t��</td>
            <td width="187"><?=$row['prodvend']?>
            </td>
            <td width="96" align="center">���</td>
            <td width="351"><?=$row['produnit']?>
            </td>
          </tr>
		   <tr> 
            <td width="103" align="center">��������</td>
            <td width="187"><?=$prodipric ?>
            </td>
            <td width="96" align="center">���</td>
            <td width="351"><?=$row['prodspric']?>
            </td>
          </tr>
          <tr> 
            <td width="103" height="22" align="center">�w���s�q</td>
            <td width="187" height="22"><?=$row['prodsave']?>             
            </td>
            <td width="96" height="22" align="center">�̪�i�f��</td>              
            <td width="187" height="22"><?=$row['prodidate']?>
            </td>
          </tr>         
         <tr>
			<td width="103" height="22" align="center">�̪�X�f��</td>
            <td width="187" height="22"><?=$row['prododate']?>			               
            </td>           
          </tr>		     
        </table>
        <br> 
		<table width="780" border="1" cellpadding="0" cellspacing="0"   bgcolor="#FFCC00"  bordercolor="#FFFFFF" align="center">
		 <tr> 
            <td width="103" height="22" align="center">����w�s�q</td>
            <td width="187" height="22">
              <input type="text" name="prodpqty" size="6" value="<?=$row[prodpqty]?>">
            </td>
            <td width="96" height="22" align="center">�{���w�s�q</td>              
            <td width="351" height="22">			   
              <input type="text" name="prodnqty"  size="6" value="<?=$row[prodnqty]?>">
            </td>
          </tr>
		  </table>          
      </td>
    </tr>
  </table>
</form>
<?
}
else
	{
	 $msg="�L�����~";
	 include("windowsclose.php");		
	} 
?>
</body>
</html>

