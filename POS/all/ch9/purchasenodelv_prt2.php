<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body >
<?php 
    // -------------���X�Ҧ��w�q������---------------
	include("mysqlcntdb.php");
	$dt=date("Y-m-d");		
	$SQLStr = "SELECT purchase.*  FROM purchase WHERE ( purchprodqty > purchinqty and purchtranno = $purchtranno)";	
	$res = mysql_query($SQLStr);
    //--------------�p���`���Ƥέ���------------------
	$total=mysql_num_rows($res);
	$lista=ceil($total/10);
?>
<!----�ǵ�purchasenodelv_prt2.php,����C�L   ---->
<form name="form1" method="post" action="purchase/purchasenodelv_prt2.php?purchtranno=' . $purcmtranno . '">
  <table width="782" border="1" align="center" cellspacing="0" cellpadding="0" >
    <tr bgcolor="#99CCFF"> 
      <td align="center">
<?php
    //--------------���ƿ�ܧe�{�γs��---------------
     echo "�w�q����f���ʸ��&nbsp;&nbsp; ��&nbsp";
	for($i = 1;$i<=$lista;$i++) 
	{
		echo "  <a href=index.php?Select=290&page=$i>$i</a>|";
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
             �����t��
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              ��f���
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              ���ʳ渹			  
            </td> 
			 <td bgcolor="#99CCFF" align="center"> 
              �q�ʼƶq			  
            </td>  
			 <td bgcolor="#99CCFF" align="center"> 
              ����ƶq			  
            </td>   
			            
          </tr>		  
	<?php
//--------------��ܭ���,���X�Ҧ��w�q�����Ƨe�{�γs�������\��-----------
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=10*($page - 1);	  
	  $SQLStr = "SELECT *  FROM purchase  WHERE ( purchprodqty > purchinqty and purchtranno = $purchtranno)";	
	  $res = mysql_query($SQLStr);
       while (list($purchtranno, $purchprodno,  $purchprodqty, $purchinqty, $purchpric)=mysql_fetch_row($res))
		{
		//------------ �����ƪ�,�w�q�����Ƨe�{----------------
            echo "<tr border='0'   bgcolor='#ffffff'>";				
			echo "<td align='center'>" . $purchprodno . "</td>\n";
			echo "<td align='center'>" . $purcmvend . "</td>\n";
			echo "<td align='center'>";
			   if ($purcmdate == '') 
			      $purcmdate="�L���";	        
			      echo  $purcmdate . "</td>\n";
            echo "<td align='center'>" . $purchtranno . "</td>\n";	
			echo "<td align='center'>" . $purchprodqty  . "</td>\n";	
			$qty= $purchprodqty - $purchinqty;
			echo "<td align='center'>" . $qty  . "</td>\n";						
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
