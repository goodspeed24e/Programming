<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?php
// -------------���X���~�����---------------	
	include("mysqlcntdb.php");
	$SQLStr = "SELECT product.* FROM product ";	
	$res = mysql_query($SQLStr);
	
//--------------�p���`���Ƥέ���------------------
	$total=mysql_num_rows($res);
	$lista=ceil($total/10);
?>
<!----����קﭶ���e�{,�ǤJ�j�M����invbasic_mod2.php------------------------->
<form name="form1" method="post" action="inv/invqty_mod2.php">

  <table width="782" border="1" align="center" cellspacing="0" cellpadding="0" >
    <tr bgcolor="#99CCFF"> 
      <td align="center">
		 <?php
//--------------���ƿ�ܧe�{�γs��---------------
     echo "�קﲣ�~�w�s���&nbsp;&nbsp; ��&nbsp";
	for($i = 1;$i<=$lista;$i++) 
	{
		echo "  <a href=index.php?Select=322&page=$i>$i</a>|";
	}
       echo "��, �@".$total."��&nbsp;&nbsp";
?> 
    </td>
    </tr>
  </table>
  <table width="782" border="0" align="center" cellpadding="0" cellspacing="0" >
    <tr> 
      <td> 
        <table width="782" border="1" align="center" bgcolor="#FFFFFF">
          <tr>                     
            <td bgcolor="#99CCFF" align="center"> 
             ���~�s��
            </td>
            <td bgcolor="#99CCFF" align="center"> 
             ���~�W��
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              �W�满��
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              �����t��
            </td>             
          </tr>		  
	<?php
//--------------��ܭ��ƾP�f���Ƨe�{�γs���קﭶ���\��-----------
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=10*($page - 1);
	  $SQLStr="select * from product order by prodno limit $first , 10";
	  $res = mysql_query($SQLStr);	 
       while (list($prodno, $prodname, $prodtype, $prodvend, $produnit, $prodipric, $prodspric, $prodsave, $prodpqty, $prodnqty, $prodgrap, $prodsdesp, $proddesp, $prodidate, $prododate)=mysql_fetch_row($res))
		{
            echo "<tr border='0'   bgcolor='#ffffff'>";	
			echo "<td align='center'>" . $prodno  . "</td>\n";
			echo "<td align='center'><a href='inv/invqty_mod2.php?prodno=" . $prodno . "'>" . $prodname . "</a></td>\n";
			echo "<td align='center'>";
			if ($prodsdesp == '') 
		         $prodsdesp="�L�W�满��";	        
			echo  $prodsdesp . "</td>\n";
			echo "<td align='center'>" . $prodvend . "</td>\n";
			echo "</tr>";		  	
		}	
?>      
        </table>
      </td>
    </tr>
  </table>    
</form>
</body>
</html>
